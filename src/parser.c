#include "parser.h"
#include "tables.h"
#include "main.h"
#include "ast.h"

// Stack to store parser states
int state_stack[STACK_SIZE] = {0};
static int state_top = -1;

// Stack to store lexemes (strings representing parsed tokens)
char *lexeme_stack[STACK_SIZE] = {NULL};
static int lexeme_top = -1;

ASTNode *get_ast_root();

// Push a parser state onto the state stack
void push_state(const int state)
{
	if (state_top == STACK_SIZE)
	{
		printf("State Stack Overflow");
		return;
	}
	state_stack[++state_top] = state;
}

// Peek the top state from the state stack without popping it
int peek_state()
{
	if (state_top == -1)
	{
		printf("Empty State Stack");
		return -1;
	}
	return state_stack[state_top];
}

// Pop the top state from the state stack
void pop_state()
{
	if (state_top == -1)
	{
		printf("State Stack Underflow");
		return;
	}
	state_top--;
}

// Push a lexeme (token value) onto the lexeme stack
void push_lexeme(const char *lexeme)
{
	if (lexeme_top == STACK_SIZE - 1)
	{
		printf("Lexeme Stack Overflow");
		return;
	}
	lexeme_stack[++lexeme_top] = strdup(lexeme); // Allocate and copy the string
}

// Peek the top lexeme from the lexeme stack without popping it
char *peek_lexeme()
{
	if (lexeme_top == -1)
	{
		printf("Empty Lexeme Stack");
		return NULL;
	}
	return lexeme_stack[lexeme_top];
}

// Pop the top lexeme from the lexeme stack and free its memory
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

void print_lexeme_stack()
{
	for (int idx = 0; idx <= lexeme_top; idx++)
	{
		printf("%s\t", lexeme_stack[idx]);
	}
	printf("\n");
}

void print_state_stack()
{
	for (int idx = 0; idx <= state_top; idx++)
	{
		printf("%d\t", state_stack[idx]);
	}
	printf("\n");
}

void reduce_by_rule(int rule_number)
{
	if (rule_number < 0 || rule_number >= 34)
	{
		fprintf(stderr, "Invalid rule number: %d\n", rule_number);
		exit(EXIT_FAILURE);
	}

	int number_of_productions = productions[rule_number].production_size;

	for (int idx = 0; idx < number_of_productions; idx++)
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
	reduce_ast(rule_number);

	int next_state = state_table[peek_state()][non_terminal_index];
	push_state(next_state);
}

// Entry point for the parser
validity parser(const char *input_file)
{
	// Initialize lexer with the input file
	if (init_lexer(input_file) == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	Token *token = get_next_token(); // Get the first token
	push_state(0);									 // Start from initial parser state

	while (1)
	{
		int current_state = peek_state();
		char *action = action_table[current_state][token->type];

		if (action == NULL)
		{
			// No valid action: parsing fails
			free_lexer();
			return INCOMPLETE;
		}

		switch (action[0])
		{
		case ACTION_ACCEPT:
			// Parsing successful
			free_lexer();
			return COMPLETE;

		case ACTION_SHIFT:
		{
			// Shift: move to next state, push current token
			int next_state = atoi(action + 1);
			push_state(next_state);
			push_lexeme(token->value);

			ASTNode *leaf = new_ast_node(token->value, 0, NULL);
			push_ast(leaf);

			token = get_next_token();
			break;
		}

		case ACTION_REDUCE:
		{
			// Reduce: apply grammar rule
			int rule_number = atoi(action + 1);
			reduce_by_rule(rule_number - 1); // Rule numbers assumed to be 1-based
			break;
		}

		case ACTION_ERROR:
		default:
			// Invalid or unexpected action: error
			free_lexer();
			printf("ERROR");
			return INCOMPLETE;
		}

		// Debug: print current state of stacks
		// print_state_stack();
		// print_lexeme_stack();
	}

	// Should not reach here under normal conditions
	free_lexer();
	return INCOMPLETE;
}
