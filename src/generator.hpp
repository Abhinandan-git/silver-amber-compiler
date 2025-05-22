#pragma once

#include "parser.hpp"
#include <cassert>

class Generator {
public:
	inline explicit Generator(NodeProgram program) : m_program(std::move(program)) {}

	inline void generate_expression(const NodeExpression* expression) {
		struct ExpressionVisitor {
			Generator* gen;

			void operator ()(const NodeExpressionIntegerLiteral* expression_integer_literal) const {
				gen->m_output << "    mov rax, " << expression_integer_literal->integer_literal.value.value() << "\n";
				gen->push("rax");
			}

			void operator ()(const NodeExpressionIdentifier* expression_identifier) {
				if (gen->m_variables.find(expression_identifier->identifier.value.value()) == gen->m_variables.end()) {
					std::cerr << "[GENERATOR] Identifier not declared: " << expression_identifier->identifier.value.value() << std::endl;
					exit(EXIT_FAILURE);
				}
				const auto var = gen->m_variables.at(expression_identifier->identifier.value.value());
				std::stringstream offset;
				offset << "QWORD [rsp + " << (gen->m_stack_size - var.stack_location - 1) * 8 << "]";
				gen->push(offset.str());
			}

			void operator ()(const NodeBinaryExpression* binary_expression) const {
				assert(false);
			}
		};

		ExpressionVisitor visitor{.gen = this};
		std::visit(visitor, expression->var);
	}

	inline void generate_statement(const NodeStatement* statement) {
		struct StatementVisitor {
			Generator* gen;

			void operator ()(const NodeStatementExit* statement_exit) const {
				gen->generate_expression(statement_exit->expression);
				gen->m_output << "    mov rax, 60\n";
				gen->pop("rdi");
				gen->m_output << "    syscall\n";
			}

			void operator ()(const NodeStatementVariable* statement_variable) const {
				if (gen->m_variables.find(statement_variable->identifier.value.value()) != gen->m_variables.end()) {
					std::cerr << "[GENERATOR] Identifier already used: " << statement_variable->identifier.value.value() << std::endl;
					exit(EXIT_FAILURE);
				}
				gen->m_variables.insert({statement_variable->identifier.value.value(), Variable {.stack_location = gen->m_stack_size}});
				gen->generate_expression(statement_variable->expression);
			}
		};

		StatementVisitor visitor{.gen = this};
		std::visit(visitor, statement->var);
	}

	[[nodiscard]] inline std::string generate_program() {
		m_output << "global _start\n_start:\n";

		for (const NodeStatement* statement : m_program.statements) {
			generate_statement(statement);
		}

		m_output << "    mov rax, 60\n";
		m_output << "    mov rdi, 0\n";
		m_output << "    syscall\n";
		return m_output.str();
	}

private:
	inline void push(const std::string reg) {
		m_output << "    push " << reg << "\n";
		m_stack_size++;
	}

	inline void pop(const std::string reg) {
		m_output << "    pop " << reg << "\n";
		m_stack_size--;
	}

	struct Variable {
		size_t stack_location;
	};

	const NodeProgram m_program;
	std::stringstream m_output;
	size_t m_stack_size = 0;
	std::unordered_map<std::string, Variable> m_variables{};
};