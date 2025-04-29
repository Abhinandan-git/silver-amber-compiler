#include "tokenizer.h"
#include "lexer.h"
#include <stdlib.h>
#include <ctype.h>

// List of keywords
const char *keywords[] = {"if", "else", "while", "return", "integer", "character", "floating", "string", "for", "break", "constant", "exit", "variable"};
const int keyword_count = sizeof(keywords) / sizeof(keywords[0]);

// List of operators
const char *operators[] = {"+", "-", "*", "/", "=", "<", ">"};
const int operator_count = sizeof(operators) / sizeof(operators[0]);

// List of punctuators
const char *punctuators[] = {";", ",", "(", ")", "{", "}", "[", "]"};
const int punctuator_count = sizeof(punctuators) / sizeof(punctuators[0]);

Token *create_token(TokenType type, const char *value)
{
	Token *token = (Token *)malloc(sizeof(Token));
	if (!token)
	{
		fprintf(stderr, "Memory allocation failed for token\n");
		exit(EXIT_FAILURE);
	}

	token->type = type;
	token->value = strdup(value); // Duplicate string to store in token
	return token;
}

int is_keyword(const char *lexeme)
{
	for (int i = 0; i < keyword_count; i++)
	{
		if (strcmp(lexeme, keywords[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int is_operator(const char *lexeme)
{
	for (int i = 0; i < operator_count; i++)
	{
		if (strcmp(lexeme, operators[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int is_punctuator(const char *lexeme)
{
	for (int i = 0; i < punctuator_count; i++)
	{
		if (strcmp(lexeme, punctuators[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

Token *compare_buffer(char *buffer, int length)
{
	if (length == 0)
	{
		return create_token(TOKEN_EOF, "EOF");
	}

	// Check if it’s a number (integer or float)
	int is_numeric = 1, has_dot = 0;
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(buffer[i]))
		{
			if (buffer[i] == '.' && !has_dot)
			{
				has_dot = 1; // Allow one dot for floating-point numbers
			}
			else
			{
				is_numeric = 0;
				break;
			}
		}
	}
	if (is_numeric)
	{
		return create_token(TOKEN_NUMBER, buffer);
	}

	// Check if it's a keyword
	if (is_keyword(buffer))
	{
		return create_token(TOKEN_KEYWORD, buffer);
	}

	// Check if it's an operator
	if (is_operator(buffer))
	{
		return create_token(TOKEN_OPERATOR, buffer);
	}

	// Check if it's a punctuator
	if (is_punctuator(buffer))
	{
		return create_token(TOKEN_PUNCTUATOR, buffer);
	}

	// If it starts with a quote, consider it a string
	if (buffer[0] == '"' && buffer[length - 1] == '"')
	{
		return create_token(TOKEN_STRING, buffer);
	}

	// If it starts with a letter or underscore, treat it as an identifier
	if (isalpha(buffer[0]) || buffer[0] == '_')
	{
		return create_token(TOKEN_IDENTIFIER, buffer);
	}

	// If nothing matches, return an error token
	return create_token(TOKEN_ERROR, buffer);
}
