#include "preprocessor.h"
#include "main.h"

validity preprocessor(const char *input_file, const char *output_file)
{
	// Opening files
	FILE *input = fopen(input_file, "r");
	FILE *output = fopen(output_file, "w");

	// Check if files opened successfully
	if (!input || !output)
	{
		fprintf_s(stderr, "Could not open file(s).");
		// Close the necessary file (Avoid memory leak)
		if (input)
		{
			fclose(input);
		}
		if (output)
		{
			fclose(output);
		}
		// Return with error code
		return INCOMPLETE;
	}

	// Get current line buffer for the file
	char current_line[BUFFER_SIZE] = {'\0'};

	while (fgets(current_line, BUFFER_SIZE, input))
	{
		// Detect directives
		if (strncmp(current_line, "#file_include", 13) == 0)
		{
			write_header_file(current_line + 13, output);
		}

		if (strncmp(current_line, "#macro", 6) == 0)
		{
			get_macro_definition(current_line + 6);
		}

		// fputs(current_line, output);
	}

	// Close files and return preprocessing successful
	fclose(input);
	fclose(output);
	return COMPLETE;
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
	fputs("\n", output);

	// Close the header file to avoid memory leak
	fclose(include_file);

	return COMPLETE;
}

validity get_macro_definition(char *current_pointer) {

}