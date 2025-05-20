#pragma once

#include "tokenization.hpp"

struct NodeExpressionIntegerLiteral {
	Token integer_literal;
};
struct NodeExpressionIdentifier {
	Token identifier;
};
struct NodeExpression {
	std::variant<NodeExpressionIntegerLiteral, NodeExpressionIdentifier> var;
};
struct NodeStatementExit {
	NodeExpression expression;
};
struct NodeStatementVariable {
	Token identifier;
	NodeExpression expression;
};
struct NodeStatement {
	std::variant<NodeStatementExit, NodeStatementVariable> var;
};
struct NodeProgram {
	std::vector<NodeStatement> statements;
};

class Parser {
public:
	inline explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}

	inline std::optional<NodeExpression> parse_expression() {
		if (peek().has_value() && peek().value().type == TokenType::t_integer_literal) {
			return NodeExpression{.var = NodeExpressionIntegerLiteral{.integer_literal = consume()}};
		} else if (peek().has_value() && peek().value().type == TokenType::t_identifier) {
			return NodeExpression{.var = NodeExpressionIdentifier{.identifier = consume()}};
		} else {
			return {};
		}
	}

	inline std::optional<NodeStatement> parse_statement() {
		if (peek().value().type == TokenType::t_exit && peek(1).has_value() && peek(1).value().type == TokenType::t_open_parenthesis) {
			consume();
			consume();
			NodeStatementExit statement_exit;
			if (std::optional<NodeExpression> node_expression = parse_expression()) {
				statement_exit = {.expression = node_expression.value()};
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
			return NodeStatement {.var = statement_exit};
		} else if (peek().has_value() && peek().value().type == TokenType::t_variable && peek(1).has_value() && peek(1).value().type == TokenType::t_identifier && peek(2).has_value() && peek(2).value().type == TokenType::t_equal) {
			consume();
			NodeStatementVariable statement_variable = NodeStatementVariable{.identifier = consume()};
			consume();
			if (auto expression = parse_expression()) {
				statement_variable.expression = expression.value();
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
			return NodeStatement{.var = statement_variable};
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
};