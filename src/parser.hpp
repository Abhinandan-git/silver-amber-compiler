#pragma once

#include "arena.hpp"
#include "tokenization.hpp"
#include <unordered_set>

struct NodeTermIntegerLiteral
{
	Token integer_literal;
};
struct NodeTermIdentifier
{
	Token identifier;
};
struct NodeExpression;
struct NodeTermParenthesis
{
	NodeExpression *expression;
};
struct NodeBinaryExpressionAddition
{
	NodeExpression *lhs;
	NodeExpression *rhs;
};
struct NodeBinaryExpressionMultiplication
{
	NodeExpression *lhs;
	NodeExpression *rhs;
};
struct NodeBinaryExpressionSubtraction
{
	NodeExpression *lhs;
	NodeExpression *rhs;
};
struct NodeBinaryExpressionDivision
{
	NodeExpression *lhs;
	NodeExpression *rhs;
};
struct NodeBinaryExpression
{
	std::variant<NodeBinaryExpressionAddition *, NodeBinaryExpressionSubtraction *, NodeBinaryExpressionMultiplication *, NodeBinaryExpressionDivision *> var;
};
struct NodeTerm
{
	std::variant<NodeTermIntegerLiteral *, NodeTermIdentifier *, NodeTermParenthesis *> var;
};
struct NodeExpression
{
	std::variant<NodeTerm *, NodeBinaryExpression *> var;
};
struct NodeStatementExit
{
	NodeExpression *expression;
};
struct NodeStatementVariable
{
	Token identifier;
	NodeExpression *expression;
};
struct NodeStatementAssignment
{
	Token identifier;
	NodeExpression *expression;
};
struct NodeStatement;
struct NodeScope
{
	std::vector<NodeStatement *> statements;
};
struct NodeStatementElse
{
	NodeScope *scope;
};
struct NodeStatementIf
{
	NodeExpression *expression;
	NodeScope *scope;
	std::optional<NodeStatementElse *> optional_else;
};
struct NodeStatementFunction
{
	Token identifier;
	NodeScope *scope;
};
struct NodeStatementCall
{
	Token identifier;
};
struct NodeStatement
{
	std::variant<NodeStatementExit *, NodeStatementVariable *, NodeScope *, NodeStatementIf *, NodeStatementAssignment *, NodeStatementFunction *, NodeStatementCall *> var;
};
struct NodeProgram
{
	std::vector<NodeStatement *> statements;
};

class Parser
{
public:
	explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)), m_allocator(1024 * 1024 * 4) {}

	std::optional<NodeTerm *> parse_term()
	{
		if (auto integer_literal = try_consume(TokenType::t_integer_literal))
		{
			auto node_term_integer_literal = m_allocator.allocate<NodeTermIntegerLiteral>();
			node_term_integer_literal->integer_literal = integer_literal.value();
			auto node_term = m_allocator.allocate<NodeTerm>();
			node_term->var = node_term_integer_literal;
			return node_term;
		}
		if (auto identifier = try_consume(TokenType::t_identifier))
		{
			auto node_term_identifier = m_allocator.allocate<NodeTermIdentifier>();
			node_term_identifier->identifier = identifier.value();
			auto node_term = m_allocator.allocate<NodeTerm>();
			node_term->var = node_term_identifier;
			return node_term;
		}
		if (auto open_parenthesis = try_consume(TokenType::t_open_parenthesis))
		{
			auto expression = parse_expression();
			if (!expression.has_value())
			{
				std::cerr << "[PARSER] Expected expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			try_consume(TokenType::t_close_parenthesis, "[PARSER] Expected `)`");
			auto term_parenthesis = m_allocator.allocate<NodeTermParenthesis>();
			term_parenthesis->expression = expression.value();
			auto term = m_allocator.allocate<NodeTerm>();
			term->var = term_parenthesis;
			return term;
		}
		return {};
	}

	std::optional<NodeExpression *> parse_expression(int minimum_precedence = 0)
	{
		std::optional<NodeTerm *> term_lhs = parse_term();
		if (!term_lhs.has_value())
		{
			return {};
		}

		auto expression_lhs = m_allocator.allocate<NodeExpression>();
		expression_lhs->var = term_lhs.value();

		while (true)
		{
			std::optional<Token> current_token = peek();
			std::optional<int> precedence;
			if (current_token.has_value())
			{
				precedence = binary_precedence(current_token->type);
				if (!precedence.has_value() || precedence < minimum_precedence)
				{
					break;
				}
			}
			else
			{
				break;
			}

			Token op = consume();
			int next_minimum_precedence = precedence.value() + 1;
			auto expression_rhs = parse_expression(next_minimum_precedence);
			if (!expression_rhs.has_value())
			{
				std::cerr << "[PARSER] Unable to parse expression" << std::endl;
				exit(EXIT_FAILURE);
			}

			auto expression = m_allocator.allocate<NodeBinaryExpression>();
			auto expression_lhs_2 = m_allocator.allocate<NodeExpression>();

			if (op.type == TokenType::t_plus)
			{
				auto add = m_allocator.allocate<NodeBinaryExpressionAddition>();
				expression_lhs_2->var = expression_lhs->var;
				add->lhs = expression_lhs_2;
				add->rhs = expression_rhs.value();
				expression->var = add;
			}
			else if (op.type == TokenType::t_star)
			{
				auto multi = m_allocator.allocate<NodeBinaryExpressionMultiplication>();
				expression_lhs_2->var = expression_lhs->var;
				multi->lhs = expression_lhs_2;
				multi->rhs = expression_rhs.value();
				expression->var = multi;
			}
			else if (op.type == TokenType::t_minus)
			{
				auto sub = m_allocator.allocate<NodeBinaryExpressionSubtraction>();
				expression_lhs_2->var = expression_lhs->var;
				sub->lhs = expression_lhs_2;
				sub->rhs = expression_rhs.value();
				expression->var = sub;
			}
			else if (op.type == TokenType::t_slash)
			{
				auto div = m_allocator.allocate<NodeBinaryExpressionDivision>();
				expression_lhs_2->var = expression_lhs->var;
				div->lhs = expression_lhs_2;
				div->rhs = expression_rhs.value();
				expression->var = div;
			}

			expression_lhs->var = expression;
		}

		return expression_lhs;
	}

	std::optional<NodeScope *> parse_scope()
	{
		if (!try_consume(TokenType::t_open_brace).has_value())
		{
			return {};
		}
		auto scope = m_allocator.allocate<NodeScope>();
		while (auto statement = parse_statement())
		{
			scope->statements.push_back(statement.value());
		}
		try_consume(TokenType::t_close_brace, "[PARSER] Expected `}`");
		return scope;
	}

	std::optional<NodeStatementElse *> parse_else()
	{
		if (try_consume(TokenType::t_else))
		{
			auto opt_else = m_allocator.allocate<NodeStatementElse>();
			if (const auto scope = parse_scope())
			{
				opt_else->scope = scope.value();
			}
			else
			{
				std::cerr << "[PARSER] Expected Scope" << std::endl;
				exit(EXIT_FAILURE);
			}
			return opt_else;
		}
		return {};
	}

	std::optional<NodeStatement *> parse_statement()
	{
		if (peek().value().type == TokenType::t_exit && peek(1).has_value() && peek(1).value().type == TokenType::t_open_parenthesis)
		{
			consume();
			consume();
			auto node_statement_exit = m_allocator.allocate<NodeStatementExit>();
			if (auto node_expression = parse_expression())
			{
				node_statement_exit->expression = node_expression.value();
			}
			else
			{
				std::cerr << "[PARSER] Invalid expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			try_consume(TokenType::t_close_parenthesis, "[PARSER] Expected `)`");
			try_consume(TokenType::t_semi_colon, "[PARSER] Expected `;`");

			auto node_statement = m_allocator.allocate<NodeStatement>();
			node_statement->var = node_statement_exit;
			return node_statement;
		}
		if (peek().has_value() && peek().value().type == TokenType::t_variable && peek(1).has_value() && peek(1).value().type == TokenType::t_identifier && peek(2).has_value() && peek(2).value().type == TokenType::t_equal)
		{
			consume();
			auto node_statement_variable = m_allocator.allocate<NodeStatementVariable>();
			node_statement_variable->identifier = consume();
			consume();
			if (auto expression = parse_expression())
			{
				node_statement_variable->expression = expression.value();
			}
			else
			{
				std::cerr << "[PARSER] Invalid expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			try_consume(TokenType::t_semi_colon, "[PARSER] Expected `;`");
			auto node_statement = m_allocator.allocate<NodeStatement>();
			node_statement->var = node_statement_variable;
			return node_statement;
		}
		if (peek().has_value() && peek().value().type == TokenType::t_identifier && peek(1).has_value() && peek(1).value().type == TokenType::t_equal)
		{
			const auto statement_assignment = m_allocator.allocate<NodeStatementAssignment>();
			statement_assignment->identifier = consume();
			consume();
			if (auto expression = parse_expression())
			{
				statement_assignment->expression = expression.value();
			}
			else
			{
				std::cerr << "[PARSER] Invalid expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			try_consume(TokenType::t_semi_colon, "[PARSER] Expected `;`");
			auto node_statement = m_allocator.emplace<NodeStatement>(statement_assignment);
			return node_statement;
		}
		if (peek().has_value() && peek().value().type == TokenType::t_function && peek(1).has_value() && peek(1).value().type == TokenType::t_identifier)
		{
			consume();
			const auto statement_function_declaration = m_allocator.allocate<NodeStatementFunction>();
			statement_function_declaration->identifier = consume();

			if (auto scope = parse_scope())
			{
				statement_function_declaration->scope = scope.value();
			}
			else
			{
				std::cerr << "Invalid Scope" << std::endl;
				exit(EXIT_FAILURE);
			}
			auto statement = m_allocator.emplace<NodeStatement>(statement_function_declaration);
			return statement;
		}
		if (peek().has_value() && peek().value().type == TokenType::t_call && peek(1).has_value() && peek(1).value().type == TokenType::t_identifier)
		{
			consume();
			const auto statement_function_call = m_allocator.allocate<NodeStatementCall>();
			statement_function_call->identifier = consume();

			try_consume(TokenType::t_semi_colon, "Expected `;`");

			auto statement = m_allocator.emplace<NodeStatement>(statement_function_call);
			return statement;
		}
		if (peek().has_value() && peek().value().type == TokenType::t_open_brace)
		{
			if (auto scope = parse_scope())
			{
				auto statement = m_allocator.allocate<NodeStatement>();
				statement->var = scope.value();
				return statement;
			}
			std::cerr << "[PARSER] Invalid Scope" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (auto if_token = try_consume(TokenType::t_if))
		{
			try_consume(TokenType::t_open_parenthesis, "Expected `(`");
			auto statement_if = m_allocator.allocate<NodeStatementIf>();
			if (auto expression = parse_expression())
			{
				statement_if->expression = expression.value();
			}
			else
			{
				std::cerr << "[PARSER] Invalid Expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			try_consume(TokenType::t_close_parenthesis, "Expected `)`");
			if (auto scope = parse_scope())
			{
				statement_if->scope = scope.value();
			}
			else
			{
				std::cerr << "[PARSER] Invalid Scope" << std::endl;
				exit(EXIT_FAILURE);
			}
			statement_if->optional_else = parse_else();
			auto statement = m_allocator.emplace<NodeStatement>(statement_if);
			return statement;
		}
		return {};
	}

	std::optional<NodeProgram> parse_program()
	{
		NodeProgram program;
		while (peek().has_value())
		{
			if (auto statement = parse_statement())
			{
				program.statements.push_back(statement.value());
			}
			else
			{
				std::cerr << "[PARSER] Invalid statement" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		return program;
	}

private:
	[[nodiscard]] std::optional<Token> peek(int offset = 0) const
	{
		if (m_current_index + offset >= m_tokens.size())
		{
			return {};
		}
		return m_tokens.at(m_current_index + offset);
	}

	Token consume()
	{
		return m_tokens.at(m_current_index++);
	}

	Token try_consume(TokenType type, std::string error_message)
	{
		if (peek().has_value() && peek().value().type == type)
		{
			return consume();
		}
		std::cerr << error_message << std::endl;
		exit(EXIT_FAILURE);
	}

	std::optional<Token> try_consume(TokenType type)
	{
		if (peek().has_value() && peek().value().type == type)
		{
			return consume();
		}
		return {};
	}

	const std::vector<Token> m_tokens;
	size_t m_current_index = 0;
	ArenaAllocator m_allocator;
};
