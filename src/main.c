#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	const char *input_file;
	const char *preprocessed_file = "data/raw_code.ffo";

	// Use the provided filename or fall back to the default
	if (argc > 1)
	{
		input_file = argv[1];
	}
	else
	{
		input_file = "data/input.ffo";
	}

	if (preprocessor(input_file, preprocessed_file) == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	if (init_lexer(preprocessed_file) == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	parser(preprocessed_file);

	return COMPLETE;
}
