#include "tokenizer.h"
#include <stdlib.h>
#include <ctype.h>

Token *create_token(TokenType type, char *value)
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

Token *compare_buffer(char *buffer, int length)
{
	if (length == 0)
	{
		return create_token(TOKEN_EOF, "EOF");
	}

	buffer[length] = '\0'; // Ensure null-terminated string

	// Check for numeric literal
	int is_numeric = 1, has_dot = 0;
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(buffer[i]))
		{
			if (buffer[i] == '.' && !has_dot)
			{
				has_dot = 1;
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
		if (has_dot)
		{
			return create_token(TOKEN_FLOAT, buffer);
		}
		else
		{
			return create_token(TOKEN_INTEGER, buffer);
		}
	}

	// Match keywords and condition operators
	if (strcmp(buffer, "for") == 0)
		return create_token(TOKEN_FOR, buffer);
	if (strcmp(buffer, "from") == 0)
		return create_token(TOKEN_FROM, buffer);
	if (strcmp(buffer, "to") == 0)
		return create_token(TOKEN_TO, buffer);
	if (strcmp(buffer, "by") == 0)
		return create_token(TOKEN_BY, buffer);
	if (strcmp(buffer, "if") == 0)
		return create_token(TOKEN_IF, buffer);
	if (strcmp(buffer, "function") == 0)
		return create_token(TOKEN_FUNCTION, buffer);

	// Conditional operators
	if (strcmp(buffer, "lt") == 0)
		return create_token(TOKEN_LT, buffer);
	if (strcmp(buffer, "gt") == 0)
		return create_token(TOKEN_GT, buffer);
	if (strcmp(buffer, "le") == 0)
		return create_token(TOKEN_LE, buffer);
	if (strcmp(buffer, "ge") == 0)
		return create_token(TOKEN_GE, buffer);
	if (strcmp(buffer, "eq") == 0)
		return create_token(TOKEN_EQ, buffer);
	if (strcmp(buffer, "ne") == 0)
		return create_token(TOKEN_NE, buffer);

	// Arithmetic and assignment operators
	if (strcmp(buffer, "+") == 0)
		return create_token(TOKEN_PLUS, buffer);
	if (strcmp(buffer, "-") == 0)
		return create_token(TOKEN_MINUS, buffer);
	if (strcmp(buffer, "*") == 0)
		return create_token(TOKEN_STAR, buffer);
	if (strcmp(buffer, "/") == 0)
		return create_token(TOKEN_SLASH, buffer);
	if (strcmp(buffer, "=") == 0)
		return create_token(TOKEN_ASSIGN, buffer);

	// Punctuators
	if (strcmp(buffer, "(") == 0)
		return create_token(TOKEN_LPAREN, buffer);
	if (strcmp(buffer, ")") == 0)
		return create_token(TOKEN_RPAREN, buffer);
	if (strcmp(buffer, "{") == 0)
		return create_token(TOKEN_LBRACE, buffer);
	if (strcmp(buffer, "}") == 0)
		return create_token(TOKEN_RBRACE, buffer);

	// Identifiers
	if (isalpha(buffer[0]) || buffer[0] == '_')
	{
		return create_token(TOKEN_IDENTIFIER, buffer);
	}

	// Fallback: unknown token
	return create_token(TOKEN_ERROR, buffer);
}
