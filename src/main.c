#include "main.h"

int main()
{
	if (preprocessor("input.ffo", "raw_code.ffo") == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	parser("raw_code.ffo");

	free_lexer();

	return COMPLETE;
}