#include "parser.h"
#include "tables.h"
#include "main.h"

validity parser(char *input_file) {
	if (init_lexer(input_file) == INCOMPLETE)
	{
		return INCOMPLETE;
	}
	Token *token = get_next_token();
	push(0);

	while (token->type != TOKEN_EOF)
	{
		
		token = get_next_token();
	}

	return COMPLETE;
}