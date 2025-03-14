#include "preprocessor.h"
#include "macro.h"
#include "main.h"

validity preprocessor(const char *input_file, const char *output_file)
{
	// Opening files
	FILE *input = fopen(input_file, "r");
	FILE *output = fopen(output_file, "w");

	// Check if files opened successfully
	if (!input || !output)
	{
		fprintf(stderr, "Could not open file(s).");
		if (input) fclose(input);
		if (output) fclose(output);
		return INCOMPLETE;
	}

	// Get current line buffer for the file
	char current_line[BUFFER_SIZE] = {'\0'};
	bool inside_block_comment = false;

	while (fgets(current_line, BUFFER_SIZE, input))
	{
		// Remove leading whitespaces
		char *trimmed_line = current_line;
		trim_leading_whitespace(&trimmed_line);

		// Detect file directives
		if (strncmp(trimmed_line, "#file_include", 13) == 0)
		{
			if (write_header_file(trimmed_line + 13, output) == INCOMPLETE) {
				return INCOMPLETE;
			}
			continue;
		}

		// Detect macro directive
		if (strncmp(trimmed_line, "#macro", 6) == 0)
		{
			if (get_macro_definition(trimmed_line + 6) == INCOMPLETE) {
				return INCOMPLETE;
			}
			continue;
		}

		char *current_character = trimmed_line;
		while (*current_character)
		{
			// Single-line comment removal ("/- ...")
			if (!inside_block_comment && *current_character == '/' && *(current_character + 1) == '-')
			{
				break; // Ignore the rest of the line
			}

			// Block comment removal ("/. ... ./")
			if (!inside_block_comment && *current_character == '/' && *(current_character + 1) == '.')
			{
				inside_block_comment = true;
				current_character += 2; // Skip "/."
				continue;
			}

			// Skip characters inside block comment
			if (inside_block_comment)
			{
				while (*current_character && !(*current_character == '.' && *(current_character + 1) == '/'))
				{
					current_character++; // Keep skipping until "./" is found
				}

				// End of block comment found
				if (*current_character == '.' && *(current_character + 1) == '/')
				{
					inside_block_comment = false;
					current_character += 2; // Skip "./"
				}
				continue; // Continue skipping
			}

			// Extract a word
			char word[BUFFER_SIZE] = {0};
			int word_index = 0;

			while (isalnum(*current_character) || *current_character == '_')
			{
				word[word_index++] = *current_character++;
			}

			if (word_index > 0)
			{
				word[word_index] = '\0';
				const char *macro_value = get_macro(word);
				if (macro_value)
				{
					fputs(macro_value, output); // Replace macro with its value
				}
				else
				{
					fputs(word, output); // Write original word
				}
			}

			// Write non-word characters as is
			if (*current_character)
			{
				fputc(*current_character, output);
				current_character++;
			}
		}
	}

	// Close files
	fclose(input);
	fclose(output);

	return COMPLETE;
}

void trim_leading_whitespace(char **line_pointer)
{
	while (**line_pointer != '\0' && isspace(**line_pointer))
	{
		// Move pointer forward
		(*line_pointer)++;
	}
}

validity write_header_file(char *current_pointer, FILE *output)
{
	// Buffer for header file name
	char include_file_name[BUFFER_SIZE] = {'\0'};

	// Extract file name from include directive
	if (sscanf(current_pointer, " <%[^>]>", include_file_name) != 1 && sscanf(current_pointer, "<%[^>]>", include_file_name) != 1)
	{
		fprintf(stderr, "Invalid #file_include format.\n");
		return INCOMPLETE;
	}

	// File object for header file
	FILE *include_file = fopen(include_file_name, "r");

	// If file did not open
	if (!include_file)
	{
		fprintf_s(stderr, "Could not include header file.");
		return INCOMPLETE;
	}

	// Buffer for header content
	char include_file_buffer[BUFFER_SIZE] = {'\0'};

	// Get the header file's content line-by-line
	while (fgets(include_file_buffer, BUFFER_SIZE, include_file))
	{
		fputs(include_file_buffer, output);
	}

	// Insert new line after header file (to be safe)
	fputc('\n', output);

	// Close the header file to avoid memory leak
	fclose(include_file);

	// File included successfully
	return COMPLETE;
}

validity get_macro_definition(char *current_pointer)
{
	char key[BUFFER_SIZE] = {'\0'}, value[BUFFER_SIZE] = {'\0'};
	if (sscanf(current_pointer, " %s %s", key, value) == 2)
	{
		insert_macro(key, value);
		return COMPLETE;
	}
	return INCOMPLETE;
}