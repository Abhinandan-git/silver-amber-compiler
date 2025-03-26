#include "parser.h"

void push(ParserStack *stack, int state, Token token)
{
	if (stack->top < STACK_SIZE - 1)
	{
		stack->items[++stack->top] = (StackElement){state, token};
	}
}

void pop(ParserStack *stack, int count)
{
	stack->top -= count;
}

StackElement top(ParserStack *stack)
{
	return stack->items[stack->top];
}