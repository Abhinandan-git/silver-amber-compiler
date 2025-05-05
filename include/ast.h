#ifndef AST_H
#define AST_H

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
void print_ast(ASTNode *node, int level);
void free_ast(ASTNode *node);

void reduce_for_loop();
void reduce_block();
void reduce_statements();
void reduce_expr();
void reduce_oprd_identifier(const char *ident);
void reduce_if_stmt();
void reduce_func_def();
void reduce_func_call();

#endif
