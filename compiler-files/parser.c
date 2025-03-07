ASTNode *create_node(TokenType type, char *lexeme, int value, ASTNode *left, ASTNode *right)
{
	ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
	node->type = type;
	if (lexeme)
		strcpy(node->lexeme, lexeme);
	node->value = value;
	node->left = left;
	node->right = right;
	return node;
}

ASTNode *parse_expression(FILE *file)
{
	Token token = get_next_token(file);

	if (token.type == TOKEN_NUMBER)
	{
		return create_node(TOKEN_NUMBER, NULL, token.value, NULL, NULL);
	}
	else if (token.type == TOKEN_ID)
	{
		return create_node(TOKEN_ID, token.lexeme, 0, NULL, NULL);
	}

	return NULL;
}

ASTNode *parse_assignment(FILE *file)
{
	Token id = get_next_token(file);
	Token assign = get_next_token(file);

	if (assign.type != TOKEN_ASSIGN)
	{
		printf("Syntax Error: Expected '='\n");
		exit(1);
	}

	ASTNode *expr = parse_expression(file);
	return create_node(TOKEN_ASSIGN, id.lexeme, 0, expr, NULL);
}

ASTNode *parse_print(FILE *file)
{
	Token token = get_next_token(file);
	if (token.type != TOKEN_ID)
	{
		printf("Syntax Error: Expected identifier in print statement\n");
		exit(1);
	}
	return create_node(TOKEN_PRINT, token.lexeme, 0, NULL, NULL);
}

ASTNode *parse_statement(FILE *file)
{
	Token token = get_next_token(file);

	if (token.type == TOKEN_INT)
	{
		return parse_assignment(file);
	}
	else if (token.type == TOKEN_PRINT)
	{
		return parse_print(file);
	}

	printf("Syntax Error: Unexpected token\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <source.ffo>\n", argv[0]);
		return 1;
	}

	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		printf("Error: Cannot open file %s\n", argv[1]);
		return 1;
	}

	printf("Parsing %s...\n", argv[1]);

	ASTNode *ast = parse_statement(file);
	fclose(file);

	printf("Parsing completed successfully.\n");
	return 0;
}
