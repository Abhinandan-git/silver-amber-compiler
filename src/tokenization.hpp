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
	t_plus
};

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
					continue;
				} else if (buffer == "variable") {
					tokens.push_back({.type = TokenType::t_variable});
					buffer.clear();
					continue;
				} else {
					tokens.push_back({.type = TokenType::t_identifier, .value = buffer});
					buffer.clear();
					continue;
				}
			} else if (std::isdigit(peek().value())) {
				buffer.push_back(consume());
				while (peek().has_value() && std::isdigit(peek().value())) {
					buffer.push_back(consume());
				}
				tokens.push_back({.type = TokenType::t_integer_literal, .value = buffer});
				buffer.clear();
				continue;
			} else if (peek().value() == ';') {
				consume();
				tokens.push_back({.type = TokenType::t_semi_colon});
				continue;
			} else if (peek().value() == '=') {
				consume();
				tokens.push_back({.type = TokenType::t_equal});
				continue;
			} else if (peek().value() == '(') {
				consume();
				tokens.push_back({.type = TokenType::t_open_parenthesis});
				continue;
			} else if (peek().value() == ')') {
				consume();
				tokens.push_back({.type = TokenType::t_close_parenthesis});
				continue;
			} else if (peek().value() == '+') {
				consume();
				tokens.push_back({.type = TokenType::t_plus});
				continue;
			} else if (std::iswspace(peek().value())) {
				consume();
				continue;
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