#include "parser.h"

int top = 0;
int state_stack[STACK_SIZE] = {};
char action_stack[STACK_SIZE] = {};

void push(int state)
{
	if (top >= STACK_SIZE - 1)
	{
		printf("Stack overflow!\n");
		exit(1);
	}
	state_stack[++top] = state;
}

int pop()
{
	if (top < 0)
	{
		printf("Stack underflow!\n");
		exit(1);
	}
	return state_stack[top--];
}

int peek()
{
	if (top < 0)
		return -1;
	return state_stack[top];
}

validity parser(const char *input_file)
{
	if (init_lexer(input_file) == INCOMPLETE)
	{
		return INCOMPLETE;
	}
	Token *lookahead_token = get_next_token();
	push(0);

	while (lookahead_token->type != TOKEN_EOF)
	{
		LexemeSymbolMap *symbol = (LexemeSymbolMap *)malloc(sizeof(LexemeSymbolMap));
		symbol->symbol = map_token_to_symbol(lookahead_token->type, lookahead_token->value);
		symbol->lexeme = malloc(strlen(lookahead_token->value) + 1);
		strcpy(symbol->lexeme, lookahead_token->value);

		free(symbol->lexeme);
		free(symbol);

		lookahead_token = get_next_token();
	}

	return COMPLETE;
}