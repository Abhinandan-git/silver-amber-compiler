#ifndef AST_H
#define AST_H

#include <stdbool.h>

typedef struct ASTNode
{
	char *lexeme;
	struct ASTNode **children;
	int child_count;
} ASTNode;

ASTNode *new_ast_node(const char *label, int n_children, ASTNode **children);
void push_ast(ASTNode *node);
ASTNode *pop_ast();
ASTNode *get_ast_root();
void print_ast(const ASTNode *, const char *, bool);
void free_ast(ASTNode *node);

void reduce_ast(int);

#endif
