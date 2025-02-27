#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_BUFFER_SIZE 33
#define ERROR_CODE -1

void lexer(FILE *);
bool check_delimiter(char);
bool check_operator(char);
bool check_keyword(char *, int);
bool check_identifier(char *);
bool check_integer(char *, int);

int main()
{
	FILE *input_file = fopen("raw_code.ffo", "r");
	if (!input_file)
	{
		printf("Input file could not be read.");
		return ERROR_CODE;
	}

	lexer(input_file);

	return 0;
}

void lexer(FILE *file)
{
	char current_character = fgetc(file);
	char buffer[MAX_BUFFER_SIZE] = {'\0'};
	int buffer_index = 0;

	while (current_character != EOF)
	{
		if (!check_delimiter(current_character))
		{
			buffer[buffer_index] = current_character;
			buffer_index++;
		}

		if (check_delimiter(current_character) && buffer_index == 1)
		{
			if (check_operator(current_character))
			{
				printf("TOKEN TYPE: OPERATOR\t%c\n", current_character);
			}
			else {
				printf("TOKEN TYPE: DELIMITER\t%c\n", current_character);
			}

			buffer_index = 0;
			memset(buffer, '\0', sizeof(char) * MAX_BUFFER_SIZE);
		}

		else if (check_delimiter(current_character) && buffer_index > 0)
		{
			if (check_keyword(buffer, buffer_index))
			{
				printf("TOKEN TYPE: KEYWORD\t%s\n", buffer);
			}
			else if (check_integer(buffer, buffer_index))
			{
				printf("TOKEN TYPE: INTEGER\t%s\n", buffer);
			}
			else if (check_identifier(buffer))
			{
				printf("TOKEN TYPE: IDENTIFIER\t%s\n", buffer);
			}
			else if (!check_identifier(buffer) && !check_delimiter(current_character))
			{
				printf("TOKEN TYPE: UNIDENTIFIED\n");
			}

			buffer_index = 0;
			memset(buffer, '\0', sizeof(char) * MAX_BUFFER_SIZE);
		}
		current_character = fgetc(file);
	}
}

bool check_delimiter(char character)
{
	return (character == ' ' || character == '+' || character == '-' || character == '*' || character == '/' || character == ',' || character == ';' || character == '%' || character == '>' || character == '<' || character == '=' || character == '(' || character == ')' || character == '[' || character == ']' || character == '{' || character == '}' || character == '`');
}

bool check_operator(char character)
{
	return (character == '+' || character == '-' || character == '*' || character == '/' || character == '>' || character == '<' || character == '=');
}

bool check_identifier(char *buffer)
{
	if (!buffer)
		return false;
	return (!isdigit(buffer[0]) && !check_delimiter(buffer[0]));
}

bool check_keyword(char *buffer, int buffer_index)
{
	const char *keywords[] = {"character", "constant", "else", "float", "for", "if", "integer", "while", "exit", "return"};

	for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
	{
		if (strcmp(buffer, keywords[i]) == 0)
		{
			return true;
		}
	}

	return false;
}

bool check_integer(char *buffer, int buffer_index)
{
	if (buffer == NULL || *buffer == '\0')
	{
		return false;
	}
	int i = 0;
	while (isdigit(buffer[i]))
	{
		i++;
	}
	return (i == buffer_index);
}