#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

enum class TokenType
{
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
	t_slash,
	t_open_brace,
	t_close_brace,
	t_if,
	t_else,
	t_function,
	t_call
};

bool is_binary_operator(TokenType type)
{
	switch (type)
	{
	case TokenType::t_plus:
	case TokenType::t_star:
		return true;

	default:
		return false;
	}
}

std::optional<int> binary_precedence(TokenType type)
{
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

struct Token
{
	TokenType type;
	std::optional<std::string> value;
};

class Tokenizer
{
public:
	explicit Tokenizer(const std::string &source) : m_source(std::move(source)) {}

	std::vector<Token> tokenize()
	{
		std::vector<Token> tokens;
		std::string buffer;
		while (peek().has_value())
		{
			if (std::isalpha(peek().value()))
			{
				buffer.push_back(consume());
				while (peek().has_value() && (std::isalnum(peek().value()) || peek().value() == '_'))
				{
					buffer.push_back(consume());
				}

				if (buffer == "exit")
				{
					tokens.push_back({.type = TokenType::t_exit});
					buffer.clear();
				}
				else if (buffer == "variable")
				{
					tokens.push_back({.type = TokenType::t_variable});
					buffer.clear();
				}
				else if (buffer == "if")
				{
					tokens.push_back({.type = TokenType::t_if});
					buffer.clear();
				}
				else if (buffer == "else")
				{
					tokens.push_back({.type = TokenType::t_else});
					buffer.clear();
				}
				else if (buffer == "function")
				{
					tokens.push_back({.type = TokenType::t_function});
					buffer.clear();
				}
				else if (buffer == "call")
				{
					tokens.push_back({.type = TokenType::t_call});
					buffer.clear();
				}
				else
				{
					tokens.push_back({.type = TokenType::t_identifier, .value = buffer});
					buffer.clear();
				}
			}
			else if (std::isdigit(peek().value()))
			{
				buffer.push_back(consume());
				while (peek().has_value() && std::isdigit(peek().value()))
				{
					buffer.push_back(consume());
				}
				tokens.push_back({.type = TokenType::t_integer_literal, .value = buffer});
				buffer.clear();
			}
			else if (peek().value() == '-' && peek(1).has_value() && peek(1).value() == '-')
			{
				consume();
				consume();
				while (peek().has_value() && peek().value() != '\n')
				{
					consume();
				}
			}
			else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '-')
			{
				consume();
				consume();
				while (peek().has_value())
				{
					if (peek().value() == '-' && peek(1).has_value() && peek(1).value() == '/')
					{
						break;
					}
					consume();
				}
				if (peek().has_value())
				{
					consume();
				}
				if (peek().has_value())
				{
					consume();
				}
			}
			else if (peek().value() == ';')
			{
				consume();
				tokens.push_back({.type = TokenType::t_semi_colon});
			}
			else if (peek().value() == '=')
			{
				consume();
				tokens.push_back({.type = TokenType::t_equal});
			}
			else if (peek().value() == '(')
			{
				consume();
				tokens.push_back({.type = TokenType::t_open_parenthesis});
			}
			else if (peek().value() == ')')
			{
				consume();
				tokens.push_back({.type = TokenType::t_close_parenthesis});
			}
			else if (peek().value() == '+')
			{
				consume();
				tokens.push_back({.type = TokenType::t_plus});
			}
			else if (peek().value() == '*')
			{
				consume();
				tokens.push_back({.type = TokenType::t_star});
			}
			else if (peek().value() == '-')
			{
				consume();
				tokens.push_back({.type = TokenType::t_minus});
			}
			else if (peek().value() == '/')
			{
				consume();
				tokens.push_back({.type = TokenType::t_slash});
			}
			else if (peek().value() == '{')
			{
				consume();
				tokens.push_back({.type = TokenType::t_open_brace});
			}
			else if (peek().value() == '}')
			{
				consume();
				tokens.push_back({.type = TokenType::t_close_brace});
			}
			else if (std::iswspace(peek().value()))
			{
				consume();
			}
			else
			{
				std::cerr << "[TOKENIZATION] Messed up!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		m_current_index = 0;
		return tokens;
	}

private:
	[[nodiscard]] std::optional<char> peek(int offset = 0) const
	{
		if (m_current_index + offset >= m_source.size())
		{
			return {};
		}
		return m_source.at(m_current_index + offset);
	}

	char consume()
	{
		return m_source.at(m_current_index++);
	}

	const std::string m_source;
	size_t m_current_index = 0;
};
