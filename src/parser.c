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

	// AST construction logic
	switch (rule_number)
	{
	case 0: // STATEMENTS → STATEMENT STATEMENTS
		reduce_statements();
		break;

	case 1: // STATEMENTS → ε
		// No AST node needed for epsilon
		break;

	case 2: // STATEMENT → FOR_LOOP
	case 3: // STATEMENT → IF_STMT
	case 4: // STATEMENT → FUNC_DEF
	case 5: // STATEMENT → FUNC_CALL
	case 6: // STATEMENT → EXPR
	case 7: // STATEMENT → COND
	case 8: // STATEMENT → ASSGNMT
		// These are wrappers; the AST node is created in the actual sub-rule
		break;

	case 9: // FOR_LOOP
		reduce_for_loop();
		break;

	case 10: // IF_STMT
		reduce_if_stmt();
		break;

	case 11: // FUNC_DEF
		reduce_func_def();
		break;

	case 12: // FUNC_CALL
		reduce_func_call();
		break;

	case 13: // ARGS → IDENTIFIER ARGS
		// Could define a reduce_args() if ARGS need to be stored in the AST
		break;

	case 14: // ARGS → ε
		break;

	case 15: // BLOCK → { STATEMENTS }
		reduce_block();
		break;

	case 16: // COND → EXPR COND_OPR EXPR
		// Could implement reduce_cond() if needed
		break;

	case 17: // EXPR → OPRD EXPR'
		reduce_expr();
		break;

	case 18: // EXPR' → OPR OPRD EXPR'
		// Could implement reduce_expr_prime() if chained ops are needed
		break;

	case 19: // EXPR' → ε
		break;

	case 20: // OPRD → LITERAL
	case 21: // OPRD → IDENTIFIER
		// Terminal reduction: push the value as a node
		// Ideally, you would pass the actual lexeme name here
		reduce_oprd_identifier("IDENTIFIER"); // Placeholder
		break;

	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32: // OPR → operators
		// These are operators; may be handled inside EXPR/COND rules
		break;

	case 33: // ASSGNMT → IDENTIFIER = EXPR
		// Could implement reduce_assignment() if needed
		break;

	default:
		// Unhandled rule
		break;
	}

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
