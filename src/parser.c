#include "parser.h"
#include "tables.h"

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

void parser(const char *input_file)
{
	init_lexer(input_file);
	Token *token = get_next_token();
	push(0);
}