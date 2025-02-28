#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#define ERROR_CODE -1
#define MAX_BUFFER_SIZE 32

typedef enum
{
	TOKEN_KEYWORD,
	TOKEN_IDENTIFIER,
	TOKEN_ASSIGNMENT,
	TOKEN_NUMBER,
	TOKEN_OPERATOR,
	TOKEN_DELIMITER,
	TOKEN_FUNCTION,
	TOKEN_EOF
} TOKEN_TYPE;

typedef struct
{
	TOKEN_TYPE type;
	char lexeme[32];
	int value;
} TOKEN;

void lexer(FILE *);
TOKEN *get_next_token(FILE *);
bool check_keyword(char *);
bool check_inbuilt_functions(char *);
bool check_operator(char);
bool check_delimiter(char);

int main()
{
	FILE *input_file = fopen("raw_code.ffo", "r");
	if (!input_file)
	{
		return ERROR_CODE;
	}

	lexer(input_file);

	fclose(input_file);
	return 0;
}

void lexer(FILE *input_file)
{
	TOKEN *token;
	do
	{
		token = get_next_token(input_file);
		printf("TOKEN: %s\nTOKEN VALUE: %d\n\n", token->lexeme, token->value);
	} while (token->type != TOKEN_EOF);
}

TOKEN *get_next_token(FILE *file)
{
	TOKEN *token = malloc(sizeof(TOKEN));
	char current_character = fgetc(file);

	token->value = 0;

	// Remove spaces
	while (isspace(current_character))
	{
		current_character = fgetc(file);
	}

	if (isalpha(current_character))
	{
		char buffer[MAX_BUFFER_SIZE] = {0};
		int buffer_index = 0;

		while (isalnum(current_character))
		{
			buffer[buffer_index++] = current_character;
			current_character = fgetc(file);
		}
		ungetc(current_character, file);

		if (check_keyword(buffer))
		{
			token->type = TOKEN_KEYWORD;
		}
		else if (check_inbuilt_functions(buffer))
		{
			token->type = TOKEN_FUNCTION;
		}
		else
		{
			token->type = TOKEN_IDENTIFIER;
		}
		strcpy(token->lexeme, buffer);

		return token;
	}

	if (isdigit(current_character))
	{
		token->type = TOKEN_NUMBER;
		strcpy(token->lexeme, "NUMBER");
		token->value = current_character - '0';
		current_character = fgetc(file);

		while (isdigit(current_character))
		{
			token->value = token->value * 10 + (current_character - '0');
			current_character = fgetc(file);
		}

		ungetc(current_character, file);
		return token;
	}

	char buffer[2] = {'\0'};
	buffer[0] = current_character;
	strcpy(token->lexeme, buffer);
	if (current_character == '=')
	{
		token->type = TOKEN_ASSIGNMENT;
	}
	else if (check_operator(current_character))
	{
		token->type = TOKEN_OPERATOR;
	}
	else if (check_delimiter(current_character))
	{
		token->type = TOKEN_DELIMITER;
	}
	else if (current_character == EOF)
	{
		token->type = TOKEN_EOF;
	}

	return token;
}

bool check_keyword(char *buffer)
{
	return !strcmp(buffer, "integer");
}

bool check_inbuilt_functions(char *buffer)
{
	return !strcmp(buffer, "print");
}

bool check_operator(char character)
{
	return (character == '+' || character == '-' || character == '*' || character == '/' || character == '>' || character == '<' || character == '=');
}

bool check_delimiter(char character)
{
	return (character == ' ' || character == '+' || character == '-' || character == '*' || character == '/' || character == ',' || character == ';' || character == '%' || character == '>' || character == '<' || character == '=' || character == '(' || character == ')' || character == '[' || character == ']' || character == '{' || character == '}');
}