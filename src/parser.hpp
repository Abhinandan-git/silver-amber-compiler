#pragma once

#include "tokenization.hpp"

struct NodeExpression {
	Token int_literal;
};
struct NodeExit {
	NodeExpression expression;
};

class Parser {
public:
	inline explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}

	inline std::optional<NodeExpression> parse_expression() {
		if (peek().has_value() && peek().value().type == TokenType::t_integer_literal) {
			return NodeExpression{.int_literal = consume()};
		} else {
			return {};
		}
	}

	inline std::optional<NodeExit> parse() {
		std::optional<NodeExit> exit_node;
		while (peek().has_value()) {
			if (peek().value().type == TokenType::t_exit && peek(1).has_value() && peek(1).value().type == TokenType::t_open_parenthesis) {
				consume();
				consume();
				if (std::optional<NodeExpression> node_expression = parse_expression()) {
					exit_node = NodeExit({.expression = node_expression.value()});
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
			}
		}

		m_current_index = 0;
		return exit_node;
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