#include "lexer.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *file_buffer = NULL; // Pointer to hold file contents

validity init_lexer(const char *input_file_name)
{
	// Open input file
	FILE *input_file = fopen(input_file_name, "r");
	if (!input_file)
	{
		fprintf(stderr, "Could not open file: %s\n", input_file_name);
		return INCOMPLETE;
	}

	// Get file size
	fseek(input_file, 0, SEEK_END);
	long long input_size = ftell(input_file);
	rewind(input_file);

	// Allocate memory for file content (+1 for null terminator)
	file_buffer = (char *)malloc(input_size + 1);
	if (!file_buffer)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		fclose(input_file);
		return INCOMPLETE;
	}

	// Read file content
	size_t read_size = fread(file_buffer, 1, input_size, input_file);
	file_buffer[read_size] = '\0'; // Null-terminate the string
	fclose(input_file);

	// Check if file was fully read
	if (read_size != input_size)
	{
		fprintf(stderr, "Error reading file.\n");
		free(file_buffer);
		return INCOMPLETE;
	}

	return COMPLETE;
}

Token *get_next_token()
{
	// Declare static pointers without initializing
	static char *lexeme_begin = NULL;
	static char *forward = NULL;

	// Initialize them only on the first call
	if (lexeme_begin == NULL || forward == NULL)
	{
		lexeme_begin = file_buffer;
		forward = file_buffer;
	}

	// Skip whitespace (modify as needed)
	while (*forward && isspace(*forward))
	{
		forward++;
	}
	lexeme_begin = forward; // Mark start of token

	// Check if we reached the end
	if (*forward == '\0')
	{
		return NULL;
	}

	// Extract token (simple example: identifier or keyword)
	while (*forward && !isspace(*forward))
	{
		forward++;
	}

	// Calculate token length
	int length = forward - lexeme_begin;

	// Create buffer and copy token
	char buffer[BUFFER_SIZE] = {'\0'};
	strncpy(buffer, lexeme_begin, length);
	buffer[length] = '\0';

	// Compare and generate token
	Token *token = compare_buffer(buffer, length);

	// Move lexeme_begin to next token
	lexeme_begin = forward;

	return token;
}

// Free allocated memory
void free_lexer()
{
	if (file_buffer)
	{
		free(file_buffer);
		file_buffer = NULL;
	}
}