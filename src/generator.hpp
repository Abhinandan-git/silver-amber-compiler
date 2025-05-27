#pragma once

#include <algorithm>
#include <unordered_map>
#include "parser.hpp"

class Generator
{
public:
	explicit Generator(NodeProgram program) : m_program(std::move(program)) {}

	void generate_term(const NodeTerm *term)
	{
		struct TermVisitor
		{
			Generator &gen;

			void operator()(const NodeTermIntegerLiteral *term_integer_literal)
			{
				gen.m_output << "    mov rax, " << term_integer_literal->integer_literal.value.value() << "\n";
				gen.push("rax");
			}

			void operator()(const NodeTermIdentifier *term_identifier)
			{
				auto it = std::find_if(gen.m_variables.cbegin(), gen.m_variables.cend(), [&](const Variable &var)
															 { return var.name == term_identifier->identifier.value.value(); });
				if (it == gen.m_variables.end())
				{
					std::cerr << "[GENERATOR] Identifier not declared: " << term_identifier->identifier.value.value() << std::endl;
					exit(EXIT_FAILURE);
				}
				std::stringstream offset;
				offset << "QWORD [rsp + " << (gen.m_stack_size - (*it).stack_location - 1) * 8 << "]";
				gen.push(offset.str());
			}

			void operator()(const NodeTermParenthesis *term_parenthesis)
			{
				gen.generate_expression(term_parenthesis->expression);
			}
		};

		TermVisitor visitor({.gen = *this});
		std::visit(visitor, term->var);
	}

	void generate_binary_expression(const NodeBinaryExpression *binary_expression)
	{
		struct BinaryExpressionVisitor
		{
			Generator &gen;

			void operator()(const NodeBinaryExpressionAddition *add) const
			{
				gen.generate_expression(add->rhs);
				gen.generate_expression(add->lhs);
				gen.pop("rax");
				gen.pop("rbx");
				gen.m_output << "    add rax, rbx\n";
				gen.push("rax");
			}

			void operator()(const NodeBinaryExpressionSubtraction *sub) const
			{
				gen.generate_expression(sub->rhs);
				gen.generate_expression(sub->lhs);
				gen.pop("rax");
				gen.pop("rbx");
				gen.m_output << "    sub rax, rbx\n";
				gen.push("rax");
			}

			void operator()(const NodeBinaryExpressionMultiplication *multi) const
			{
				gen.generate_expression(multi->rhs);
				gen.generate_expression(multi->lhs);
				gen.pop("rax");
				gen.pop("rbx");
				gen.m_output << "    mul rbx\n";
				gen.push("rax");
			}

			void operator()(const NodeBinaryExpressionDivision *div) const
			{
				gen.generate_expression(div->rhs);
				gen.generate_expression(div->lhs);
				gen.pop("rax");
				gen.pop("rbx");
				gen.m_output << "    div rbx\n";
				gen.push("rax");
			}
		};

		BinaryExpressionVisitor visitor({.gen = *this});
		std::visit(visitor, binary_expression->var);
	}

	void generate_expression(const NodeExpression *expression)
	{
		struct ExpressionVisitor
		{
			Generator &gen;

			void operator()(const NodeTerm *term) const
			{
				gen.generate_term(term);
			}

			void operator()(const NodeBinaryExpression *binary_expression) const
			{
				gen.generate_binary_expression(binary_expression);
			}
		};

		ExpressionVisitor visitor{.gen = *this};
		std::visit(visitor, expression->var);
	}

	void generate_scope(const NodeScope *scope)
	{
		begin_scope();
		for (const NodeStatement *statement : scope->statements)
		{
			generate_statement(statement);
		}
		end_scope();
	}

	void generate_else(const NodeStatementElse *opt_else) {
		generate_scope(opt_else->scope);
	}

	void generate_statement(const NodeStatement *statement)
	{
		struct StatementVisitor
		{
			Generator &gen;

			void operator()(const NodeStatementExit *statement_exit) const
			{
				gen.generate_expression(statement_exit->expression);
				gen.m_output << "    mov rax, 60\n";
				gen.pop("rdi");
				gen.m_output << "    syscall\n";
			}

			void operator()(const NodeStatementVariable *statement_variable) const
			{
				if (std::find_if(gen.m_variables.crbegin(), gen.m_variables.crend(), [&](const Variable &var)
												 { return var.name == statement_variable->identifier.value.value(); }) != gen.m_variables.crend())
				{
					std::cerr << "[GENERATOR] Identifier already used: " << statement_variable->identifier.value.value() << std::endl;
					exit(EXIT_FAILURE);
				}
				gen.m_variables.push_back({.name = statement_variable->identifier.value.value(), .stack_location = gen.m_stack_size});
				gen.generate_expression(statement_variable->expression);
			}

			void operator()(const NodeStatementAssignment *statement_assignment) const
			{
				auto it = std::find_if(gen.m_variables.cbegin(), gen.m_variables.cend(), [&](const Variable &var)
												 { return var.name == statement_assignment->identifier.value.value(); });
				if (it == gen.m_variables.cend())
				{
					std::cerr << "[GENERATOR] Identifier not declared: " << statement_assignment->identifier.value.value() << std::endl;
					exit(EXIT_FAILURE);
				}
				gen.generate_expression(statement_assignment->expression);
				gen.pop("rax");
				gen.m_output << "    mov [rsp + " << (gen.m_stack_size - (*it).stack_location - 1) * 8 << "], rax\n";
			}

			void operator()(const NodeScope *statement_scope) const
			{
				gen.generate_scope(statement_scope);
			}

			void operator()(const NodeStatementIf *statement_if) const
			{
				gen.generate_expression(statement_if->expression);
				gen.pop("rax");
				std::string if_label = gen.create_label();
				gen.m_output << "    test rax, rax\n";
				gen.m_output << "    jz " << if_label << "\n";
				gen.generate_scope(statement_if->scope);
				std::string end_label;
				if (statement_if->optional_else.has_value()) {
					end_label = gen.create_label();
					gen.m_output << "    jmp " << end_label << "\n";
				}
				gen.m_output << if_label << ":\n";
				if (statement_if->optional_else.has_value()) {
					gen.generate_else(statement_if->optional_else.value());
					gen.m_output << end_label << ":\n";
				}
			}

			void operator()(const NodeStatementFunction *statement_function) const {
				std::string function_end_label = gen.create_label();
				gen.m_output << "    jmp " << function_end_label << "\n";

				std::string function_label = gen.create_function_label();
				gen.m_function_labels[statement_function->identifier.value.value()] = function_label;

				gen.m_variables.push_back({.name = statement_function->identifier.value.value(), .stack_location = gen.m_stack_size});

				gen.m_output << function_label << ":\n";
				gen.generate_scope(statement_function->scope);
				
				gen.m_output << "    ret\n";
				gen.m_output << function_end_label << ":\n";
			}

			void operator()(const NodeStatementCall *statement_call) const {
				gen.m_output << "    call " << gen.m_function_labels[statement_call->identifier.value.value()] << "\n";
			}
		};

		StatementVisitor visitor{.gen = *this};
		std::visit(visitor, statement->var);
	}

	[[nodiscard]] std::string generate_program()
	{
		m_output << "global _start\n_start:\n";

		for (const NodeStatement *statement : m_program.statements)
		{
			generate_statement(statement);
		}

		m_output << "    mov rax, 60\n";
		m_output << "    mov rdi, 0\n";
		m_output << "    syscall\n";
		return m_output.str();
	}

private:
	void push(const std::string reg)
	{
		m_output << "    push " << reg << "\n";
		m_stack_size++;
	}

	void pop(const std::string reg)
	{
		m_output << "    pop " << reg << "\n";
		m_stack_size--;
	}

	void begin_scope()
	{
		m_scopes.push_back(m_variables.size());
	}

	void end_scope()
	{
		size_t pop_count = m_variables.size() - m_scopes.back();
		m_output << "    add rsp, " << pop_count * 8 << "\n";
		m_stack_size -= pop_count;
		for (int _ = 0; _ < pop_count; _++)
		{
			m_variables.pop_back();
		}
		m_scopes.pop_back();
	}

	std::string create_label()
	{
		std::stringstream ss;
		ss << "label" << m_label_count++;
		return ss.str();
	}

	std::string create_function_label()
	{
		std::stringstream ss;
		ss << "flabel" << m_function_label_count++;
		return ss.str();
	}

	struct Variable
	{
		std::string name;
		size_t stack_location;
	};

	const NodeProgram m_program;
	std::stringstream m_output;
	size_t m_stack_size = 0;
	std::vector<Variable> m_variables{};
	std::vector<size_t> m_scopes{};
	int m_label_count = 0;
	int m_function_label_count = 0;
	std::unordered_map<std::string, std::string> m_function_labels{};
};