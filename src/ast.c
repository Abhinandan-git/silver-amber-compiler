#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "tables.h"

#define MAX_CHILDREN 10

// Stack for constructing the AST during parsing
static ASTNode *ast_stack[1000];
static int ast_top = -1; // Stack top index

// Recursively print the AST in a tree-like format
void print_ast(const ASTNode *node, const char *prefix, bool is_last)
{
	if (!node)
		return;

	// Print the current node with the tree branch formatting
	printf("%s%s%s\n", prefix, is_last ? "+-- " : "|-- ", node->lexeme);

	// Prepare prefix for the children
	char new_prefix[1024];
	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "|   ");

	for (int i = 0; i < node->child_count; ++i)
	{
		bool last = (i == node->child_count - 1);
		print_ast(node->children[i], new_prefix, last);
	}
}

// Push an AST node onto the stack
void push_ast(ASTNode *node)
{
	if (ast_top >= 999)
	{
		printf("[AST] Stack Overflow\n");
		return;
	}
	ast_stack[++ast_top] = node;
}

// Pop an AST node from the stack
ASTNode *pop_ast()
{
	if (ast_top < 0)
	{
		printf("[AST] Stack Underflow\n");
		return NULL;
	}
	return ast_stack[ast_top--];
}

// Retrieve the root node of the AST
ASTNode *get_ast_root()
{
	if (ast_top < 0)
		return NULL;
	return ast_stack[ast_top];
}

// Allocate and initialize a new AST node
ASTNode *new_ast_node(const char *lexeme, int n_children, ASTNode **children)
{
	ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
	node->lexeme = strdup(lexeme);
	node->child_count = n_children;
	node->children = NULL;
	if (n_children > 0)
	{
		node->children = (ASTNode **)malloc(sizeof(ASTNode *) * n_children);
		for (int i = 0; i < n_children; ++i)
		{
			node->children[i] = children[i];
		}
	}
	return node;
}

// Recursively free all memory associated with the AST
void free_ast(ASTNode *node)
{
	if (!node)
		return;
	for (int i = 0; i < node->child_count; ++i)
	{
		free_ast(node->children[i]);
	}
	free(node->children);
	free(node->lexeme);
	free(node);
}

// Reduce the AST by applying the grammar rule with the given rule number
void reduce_ast(int rule_number)
{
	if (rule_number < 0 || rule_number >= 34)
	{
		fprintf(stderr, "[AST] Invalid rule number: %d\n", rule_number);
		exit(EXIT_FAILURE);
	}

	Productions rule = productions[rule_number];
	int n = rule.production_size;

	// Collect the children in reverse order (LIFO stack)
	ASTNode **children = NULL;
	if (n > 0)
	{
		children = (ASTNode **)malloc(sizeof(ASTNode *) * n);
		for (int i = n - 1; i >= 0; --i)
		{
			children[i] = pop_ast();
			if (!children[i])
			{
				fprintf(stderr, "[AST] Error: Not enough AST nodes on stack for rule %d\n", rule_number);
				exit(EXIT_FAILURE);
			}
		}
	}

	// Create the new AST node using the non-terminal on the left-hand side
	ASTNode *node = new_ast_node(rule.non_terminal, n, children);

	// Clean up temporary children array
	free(children);

	// Push the new node onto the AST stack
	push_ast(node);
}
