#pragma once

#include "arena.hpp"
#include "tokenization.hpp"

struct NodeExpressionIntegerLiteral {
	Token integer_literal;
};
struct NodeExpressionIdentifier {
	Token identifier;
};
struct NodeExpression;
struct NodeBinaryExpressionAddition {
	NodeExpression *lhs;
	NodeExpression *rhs;
};
struct NodeBinaryExpressionMultiplication {
	NodeExpression *lhs;
	NodeExpression *rhs;
};
struct NodeBinaryExpression {
	std::variant<NodeBinaryExpressionAddition *, NodeBinaryExpressionMultiplication *> var;
};
struct NodeExpression {
	std::variant<NodeExpressionIntegerLiteral*, NodeExpressionIdentifier*, NodeBinaryExpression *> var;
};
struct NodeStatementExit {
	NodeExpression *expression;
};
struct NodeStatementVariable {
	Token identifier;
	NodeExpression *expression;
};
struct NodeStatement {
	std::variant<NodeStatementExit *, NodeStatementVariable *> var;
};
struct NodeProgram {
	std::vector<NodeStatement *> statements;
};

class Parser {
public:
	inline explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)), m_allocator(1024 * 1024 * 4) {}

	inline std::optional<NodeExpression*> parse_expression() {
		if (peek().has_value() && peek().value().type == TokenType::t_integer_literal) {
			auto node_expression_integer_literal = m_allocator.allocate<NodeExpressionIntegerLiteral>();
			node_expression_integer_literal->integer_literal = consume();
			auto node_expression = m_allocator.allocate<NodeExpression>();
			node_expression->var = node_expression_integer_literal;
			return node_expression;
		} else if (peek().has_value() && peek().value().type == TokenType::t_identifier) {
			auto node_expression_identifier = m_allocator.allocate<NodeExpressionIdentifier>();
			node_expression_identifier->identifier = consume();
			auto node_expression = m_allocator.allocate<NodeExpression>();
			node_expression->var = node_expression_identifier;
			return node_expression;
		} else {
			return {};
		}
	}

	inline std::optional<NodeStatement *> parse_statement() {
		if (peek().value().type == TokenType::t_exit && peek(1).has_value() && peek(1).value().type == TokenType::t_open_parenthesis) {
			consume();
			consume();
			auto node_statement_exit = m_allocator.allocate<NodeStatementExit>();
			if (auto node_expression = parse_expression()) {
				node_statement_exit->expression = node_expression.value();
			} else {
				std::cerr << "[PARSER] Invalid expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			if (peek().has_value() && peek().value().type == TokenType::t_close_parenthesis) {
				consume();
			} else {
				std::cerr << "[PARSER] Expected `)`" << std::endl;
				exit(EXIT_FAILURE);
			}
			if (peek().has_value() && peek().value().type == TokenType::t_semi_colon) {
				consume();
			} else {
				std::cerr << "[PARSER] Expected `;`" << std::endl;
				exit(EXIT_FAILURE);
			}
			auto node_statement = m_allocator.allocate<NodeStatement>();
			node_statement->var = node_statement_exit;
			return node_statement;
		} else if (peek().has_value() && peek().value().type == TokenType::t_variable && peek(1).has_value() && peek(1).value().type == TokenType::t_identifier && peek(2).has_value() && peek(2).value().type == TokenType::t_equal) {
			consume();
			auto node_statement_variable = m_allocator.allocate<NodeStatementVariable>();
			node_statement_variable->identifier = consume();
			consume();
			if (auto expression = parse_expression()) {
				node_statement_variable->expression = expression.value();
			} else {
				std::cerr << "[PARSER] Invalid expression" << std::endl;
				exit(EXIT_FAILURE);
			}
			if (peek().has_value() && peek().value().type == TokenType::t_semi_colon) {
				consume();
			} else {
				std::cerr << "[PARSER] Expected `;`" << std::endl;
				exit(EXIT_FAILURE);
			}
			auto node_statement = m_allocator.allocate<NodeStatement>();
			node_statement->var = node_statement_variable;
			return node_statement;
		} else {
			return {};
		}
	}

	inline std::optional<NodeProgram> parse_program() {
		NodeProgram program;
		while (peek().has_value()) {
			if (auto statement = parse_statement()) {
				program.statements.push_back(statement.value());
			} else {
				std::cerr << "[PARSER] Invalid statement" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		return program;
	}

private:
	[[nodiscard]] inline std::optional<Token> peek(int offset = 0) const {
		if (m_current_index + offset >= m_tokens.size()) {
			return {};
		} else {
			return m_tokens.at(m_current_index + offset);
		}
	}

	inline Token consume() {
		return m_tokens.at(m_current_index++);
	}

	const std::vector<Token> m_tokens;
	size_t m_current_index = 0;
	ArenaAllocator m_allocator;
};