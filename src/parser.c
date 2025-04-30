#include "parser.h"
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
		Token *lookahead_token = peek_token();
		
		token = get_next_token();
	}

	return COMPLETE;
}