#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

#define MAX_CHILDREN 10

// Stack for constructing the AST during parsing
static ASTNode *ast_stack[1000];
static int ast_top = -1; // Stack top index

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

// Recursively print the AST with indentation
void print_ast(ASTNode *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("%s\n", node->lexeme);
	for (int i = 0; i < node->child_count; i++)
	{
		print_ast(node->children[i], level + 1);
	}
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

// AST grammar reduction implementations

void reduce_for_loop()
{
	ASTNode *block = pop_ast();
	pop_ast(); // ")"
	ASTNode *by = pop_ast();
	pop_ast(); // "by"
	ASTNode *to = pop_ast();
	pop_ast(); // "to"
	ASTNode *from = pop_ast();
	pop_ast(); // "from"
	ASTNode *oprd = pop_ast();
	pop_ast(); // "("
	pop_ast(); // "for"

	ASTNode *children[] = {oprd, from, to, by, block};
	ASTNode *node = new_ast_node("FOR_LOOP", 5, children);
	push_ast(node);
}

void reduce_block()
{
	pop_ast(); // "}"
	ASTNode *stmts = pop_ast();
	pop_ast(); // "{"

	ASTNode *children[] = {stmts};
	ASTNode *node = new_ast_node("BLOCK", 1, children);
	push_ast(node);
}

void reduce_statements()
{
	ASTNode *stmts = pop_ast();
	ASTNode *stmt = pop_ast();

	ASTNode *children[] = {stmt, stmts};
	ASTNode *node = new_ast_node("STATEMENTS", 2, children);
	push_ast(node);
}

void reduce_expr()
{
	ASTNode *expr_dash = pop_ast();
	ASTNode *oprd = pop_ast();

	ASTNode *children[] = {oprd, expr_dash};
	ASTNode *node = new_ast_node("EXPR", 2, children);
	push_ast(node);
}

void reduce_oprd_identifier(const char *ident)
{
	ASTNode *node = new_ast_node(ident, 0, NULL);
	push_ast(node);
}

void reduce_if_stmt()
{
	ASTNode *block = pop_ast();
	pop_ast(); // ")"
	ASTNode *cond = pop_ast();
	pop_ast(); // "("
	pop_ast(); // "if"

	ASTNode *children[] = {cond, block};
	ASTNode *node = new_ast_node("IF_STMT", 2, children);
	push_ast(node);
}

void reduce_func_def()
{
	ASTNode *block = pop_ast();
	pop_ast(); // ")"
	ASTNode *args = pop_ast();
	pop_ast(); // "("
	ASTNode *ident = pop_ast();
	pop_ast(); // "function"

	ASTNode *children[] = {ident, args, block};
	ASTNode *node = new_ast_node("FUNC_DEF", 3, children);
	push_ast(node);
}

void reduce_func_call()
{
	pop_ast(); // ")"
	ASTNode *args = pop_ast();
	pop_ast(); // "("
	ASTNode *ident = pop_ast();

	ASTNode *children[] = {ident, args};
	ASTNode *node = new_ast_node("FUNC_CALL", 2, children);
	push_ast(node);
}
