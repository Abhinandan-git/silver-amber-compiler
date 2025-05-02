#include "parser.h"
#include "tables.h"
#include "main.h"

int state_stack[STACK_SIZE] = {0};
static int state_top = -1;
char *lexeme_stack[STACK_SIZE] = {NULL};
static int lexeme_top = -1;

void push_state(const int state)
{
	if (state_top == STACK_SIZE)
	{
		printf("State Stack Overflow");
		return;
	}
	state_stack[++state_top] = state;
}

int peek_state()
{
	if (state_top == -1)
	{
		printf("Empty State Stack");
		return -1;
	}
	return state_stack[state_top];
}

void pop_state()
{
	if (state_top == -1)
	{
		printf("State Stack Underflow");
		return;
	}
	state_top--;
}

void push_lexeme(const char *lexeme)
{
	if (lexeme_top == STACK_SIZE - 1)
	{
		printf("Lexeme Stack Overflow");
		return;
	}
	lexeme_stack[++lexeme_top] = strdup(lexeme);
}

char *peek_lexeme()
{
	if (lexeme_top == -1)
	{
		printf("Empty Lexeme Stack");
		return NULL;
	}
	return lexeme_stack[lexeme_top];
}

void pop_lexeme()
{
	if (lexeme_top == -1)
	{
		printf("Lexeme Stack Underflow");
		return;
	}
	free(lexeme_stack[lexeme_top]);
	lexeme_stack[lexeme_top--] = NULL;
}

void reduce_by_rule(int rule_number)
{
	if (rule_number < 0 || rule_number >= 30)
	{
		fprintf(stderr, "Invalid rule number: %d\n", rule_number);
		exit(EXIT_FAILURE);
	}

	int number_of_productions = productions[rule_number].production_size;

	for (int i = 0; i < number_of_productions; i++)
	{
		pop_lexeme();
		pop_state();
	}

	char *non_terminal = productions[rule_number].non_terminal;
	int non_terminal_index = get_non_terminal_index(non_terminal);
	if (non_terminal_index < 0)
	{
		fprintf(stderr, "Unknown non-terminal: %s\n", non_terminal);
		exit(EXIT_FAILURE);
	}

	push_lexeme(non_terminal);

	int next_state = state_table[peek_state()][non_terminal_index];
	push_state(next_state);
}

validity parser(const char *input_file)
{
	if (init_lexer(input_file) == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	Token *token = get_next_token();
	push_state(0);

	while (1)
	{
		int current_state = peek_state();
		char *action = action_table[current_state][token->type];

		if (action == NULL)
		{
			free_lexer();
			return INCOMPLETE; // Unknown action
		}

		switch (action[0])
		{
		case ACTION_ACCEPT: // accept
			free_lexer();
			printf("ACCEPT");
			return COMPLETE;
		case ACTION_SHIFT:
		{
			int next_state = atoi(action + 1);
			push_state(next_state);
			push_lexeme(token->value);
			token = get_next_token();
			break;
		}
		case ACTION_REDUCE:
		{ // reduce
			int rule_number = atoi(action + 1);
			reduce_by_rule(rule_number - 1);
			break;
		}
		case ACTION_ERROR: // error
		default:
			free_lexer();
			printf("ERROR");
			return INCOMPLETE;
		}

		// print_state_stack();
		// print_lexeme_stack();
	}

	free_lexer();
	return INCOMPLETE; // Shouldn't get here
}
