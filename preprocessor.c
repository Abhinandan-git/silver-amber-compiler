#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FILE_SIZE 50000
#define ERROR_CODE -1

int preprocess(FILE *, char *);
bool check_operator(char);

int main()
{
	FILE *input_file = fopen("code.ffo", "r");
	if (!input_file)
	{
		printf("Input file could not be read.");
		return ERROR_CODE;
	}

	char buffer[MAX_FILE_SIZE] = {0};
	if (!buffer)
	{
		return ERROR_CODE;
	}
	int buffer_index = preprocess(input_file, buffer);

	FILE *output_file = fopen("raw_code.ffo", "w");
	if (!output_file)
	{
		printf("Output file could not be created.");
		return ERROR_CODE;
	}

	fwrite(buffer, sizeof(char), buffer_index, output_file);

	return 0;
}

int preprocess(FILE *file, char *buffer)
{
	char current_character = fgetc(file);

	int buffer_index = 0;

	while (current_character != EOF)
	{
		// Removing comments
		if (current_character == '`')
		{
			while (current_character != '\n' && current_character != EOF)
			{
				current_character = fgetc(file);
			}
			continue;
		}

		// Removing extra whitespaces and newlines
		if ((current_character == ' ' || current_character == '\t') && (check_operator(buffer[buffer_index - 1]) || buffer[buffer_index - 1] == ' ' || buffer[buffer_index - 1] == ';') || current_character == '\n')
		{
			current_character = fgetc(file);
			continue;
		}

		if (current_character == '\t')
		{
			current_character = ' ';
		}

		if (check_operator(current_character))
		{
			buffer[buffer_index - 1] = current_character;
		}
		else
		{
			buffer[buffer_index] = current_character;
			buffer_index++;
		}
		current_character = fgetc(file);
	}

	buffer[buffer_index] = '\0';

	return buffer_index;
}

bool check_operator(char character)
{
	return (character == '+' || character == '-' || character == '*' || character == '/' || character == '>' || character == '<' || character == '=');
}