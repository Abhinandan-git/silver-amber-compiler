#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

// Macros for constants
#define ERROR_CODE -1
#define MAX_BUFFER_SIZE 33
#define MAX_TOKENS 50000

// Generating the type of token
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

// Structure of a token
typedef struct
{
	TOKEN_TYPE type;
	char lexeme[32];
	int value;
} TOKEN;

// Function declarations
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

// Generating all token one-by-one
void lexer(FILE *input_file)
{
	TOKEN all_tokens[MAX_TOKENS] = {0};
	int token_index = 0;
	TOKEN *token;

	do
	{
		// Generate the next token
		token = get_next_token(input_file);
		// Storing the token generated
		all_tokens[token_index++] = token;
		printf("TOKEN: %s\nTOKEN VALUE: %d\n\n", token->lexeme, token->value);
		// Repeat until EOF is encountered
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

	// Check for keywords and identifiers
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

		// Check if keyword is found
		if (check_keyword(buffer))
		{
			token->type = TOKEN_KEYWORD;
		}
		// Check for any inbuilt functions
		else if (check_inbuilt_functions(buffer))
		{
			token->type = TOKEN_FUNCTION;
		}
		// An identifier is found
		else
		{
			token->type = TOKEN_IDENTIFIER;
		}
		// Copy the lexeme to the token
		strcpy(token->lexeme, buffer);

		return token;
	}

	// A number is found (outside of the literal) (only integers so far)
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

	// Check for operators and delimiters
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
	return (!strcmp(buffer, "integer") || !strcmp(buffer, "float") || !strcmp(buffer, "string") || !strcmp(buffer, "character") || !strcmp(buffer, "void") || !strcmp(buffer, "if") || !strcmp(buffer, "else") || !strcmp(buffer, "for") || !strcmp(buffer, "while") || !strcmp(buffer, "return"));
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