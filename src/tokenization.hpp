#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

enum class TokenType {
	t_exit,
	t_integer_literal,
	t_semi_colon,
	t_open_parenthesis,
	t_close_parenthesis,
	t_identifier,
	t_variable,
	t_equal,
	t_plus,
	t_star,
	t_minus,
	t_slash
};

bool is_binary_operator(TokenType type) {
	switch (type)
	{
	case TokenType::t_plus:
	case TokenType::t_star:
		return true;
	
	default:
		return false;
	}
}

std::optional<int> binary_precedence(TokenType type) {
	switch (type)
	{
	case TokenType::t_plus:
	case TokenType::t_minus:
		return 0;
	case TokenType::t_star:
	case TokenType::t_slash:
		return 1;
	default:
		return {};
	}
}

struct Token {
	TokenType type;
	std::optional<std::string> value;
};

class Tokenizer {
public:
	inline explicit Tokenizer(const std::string& source) : m_source(std::move(source)) {}

	inline std::vector<Token> tokenize() {
		std::vector<Token> tokens;
		std::string buffer;
		while (peek().has_value()) {
			if (std::isalpha(peek().value())) {
				buffer.push_back(consume());
				while (peek().has_value() && std::isalnum(peek().value())) {
					buffer.push_back(consume());
				}

				if (buffer == "exit") {
					tokens.push_back({.type = TokenType::t_exit});
					buffer.clear();
				} else if (buffer == "variable") {
					tokens.push_back({.type = TokenType::t_variable});
					buffer.clear();
				} else {
					tokens.push_back({.type = TokenType::t_identifier, .value = buffer});
					buffer.clear();
				}
			} else if (std::isdigit(peek().value())) {
				buffer.push_back(consume());
				while (peek().has_value() && std::isdigit(peek().value())) {
					buffer.push_back(consume());
				}
				tokens.push_back({.type = TokenType::t_integer_literal, .value = buffer});
				buffer.clear();
			} else if (peek().value() == ';') {
				consume();
				tokens.push_back({.type = TokenType::t_semi_colon});
			} else if (peek().value() == '=') {
				consume();
				tokens.push_back({.type = TokenType::t_equal});
			} else if (peek().value() == '(') {
				consume();
				tokens.push_back({.type = TokenType::t_open_parenthesis});
			} else if (peek().value() == ')') {
				consume();
				tokens.push_back({.type = TokenType::t_close_parenthesis});
			} else if (peek().value() == '+') {
				consume();
				tokens.push_back({.type = TokenType::t_plus});
			} else if (peek().value() == '*') {
				consume();
				tokens.push_back({.type = TokenType::t_star});
			} else if (peek().value() == '-') {
				consume();
				tokens.push_back({.type = TokenType::t_minus});
			} else if (peek().value() == '/') {
				consume();
				tokens.push_back({.type = TokenType::t_slash});
			} else if (std::iswspace(peek().value())) {
				consume();
			} else {
				std::cerr << "[TOKENIZATION] Messed up!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		m_current_index = 0;
		return tokens;
	}

private:
	[[nodiscard]] inline std::optional<char> peek(int ahead = 1) const {
		if (m_current_index + ahead > m_source.size()) {
			return {};
		} else {
			return m_source.at(m_current_index);
		}
	}

	inline char consume() {
		return m_source.at(m_current_index++);
	}

	const std::string m_source;
	size_t m_current_index = 0;
};