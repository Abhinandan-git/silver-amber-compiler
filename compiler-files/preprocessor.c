#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A code with 500k characters
#define MAX_FILE_SIZE 500001
// Error code to debug the defect
#define ERROR_CODE -1

// Function declarations
int preprocess(FILE *, char *);
bool check_operator(char);

// Main function to run
int main()
{
	// Opening main source code file
	FILE *input_file = fopen("code.ffo", "r");
	// If file failes to open
	if (!input_file)
	{
		printf("Input file could not be read.");
		return ERROR_CODE;
	}

	// Get the buffer size of original code file with inital 0s
	char buffer[MAX_FILE_SIZE] = {0};
	if (!buffer)
	{
		return ERROR_CODE;
	}
	// Preprocess the file to generate raw file
	int buffer_index = preprocess(input_file, buffer);

	// Open an output file to put the raw file
	FILE *output_file = fopen("raw_code.ffo", "w");
	// Give error if output file fails to open
	if (!output_file)
	{
		printf("Output file could not be created.");
		return ERROR_CODE;
	}

	// Writing the raw code to a file
	fwrite(buffer, sizeof(char), buffer_index, output_file);

	return 0;
}

int preprocess(FILE *file, char *buffer)
{
	char current_character = fgetc(file);

	int buffer_index = 0;

	while (current_character != EOF)
	{
		// Removing comments (`)
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

		// Replacing tabs with a space
		if (current_character == '\t')
		{
			current_character = ' ';
		}

		// Removing spaces before the operator
		if (check_operator(current_character))
		{
			buffer[buffer_index - 1] = current_character;
		}
		// Characters get written to the output file
		else
		{
			buffer[buffer_index] = current_character;
			buffer_index++;
		}
		current_character = fgetc(file);
	}

	// End the file to ensure no data leaks
	buffer[buffer_index] = '\0';

	return buffer_index;
}

// Function to check for operators
bool check_operator(char character)
{
	return (character == '+' || character == '-' || character == '*' || character == '/' || character == '>' || character == '<' || character == '=');
}