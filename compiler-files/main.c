#include "main.h"

int main()
{
	if (preprocessor("file.ffo", "raw_code.ffo") == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	if (init_lexer("raw_code.ffo") == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	TOKEN *token = get_next_token();
	do
	{
		printf("TOKEN TYPE: %d\tLEXEME: %s\n", token->type, token->value);
		free(token);
		token = get_next_token();
	} while (token->type != TOKEN_EOF);

	free_lexer();

	return COMPLETE;
}