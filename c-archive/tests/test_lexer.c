#include "main.h"
#include "lexer.h"

void test_lexer(const char *input, int expected_token)
{
	init_lexer(input); // Assume this function initializes the lexer with the given input
	Token *token = get_next_token();

	if (token->type == expected_token)
	{
		printf("PASSED: %s -> Token %d\n", input, token->type);
	}
	else
	{
		printf("FAILED: %s -> Expected %d but got %d\n", input, expected_token, token->type);
	}
}

int main()
{
	// Test keywords
	test_lexer("if", TOKEN_KEYWORD);
	test_lexer("else", TOKEN_KEYWORD);
	test_lexer("return", TOKEN_KEYWORD);

	// Test identifiers
	test_lexer("variableName", TOKEN_IDENTIFIER);
	test_lexer("_tempVar", TOKEN_IDENTIFIER);
	test_lexer("myFunc123", TOKEN_IDENTIFIER);

	// Test numbers
	test_lexer("123", TOKEN_NUMBER);
	test_lexer("3.14", TOKEN_NUMBER);
	test_lexer("0xFF", TOKEN_NUMBER);

	// Test strings
	test_lexer("\"Hello, World!\"", TOKEN_STRING);
	test_lexer("\"\"", TOKEN_STRING);
	test_lexer("\"Escape\\\"Test\"", TOKEN_STRING);

	// Test operators
	test_lexer("+", TOKEN_OPERATOR);
	test_lexer("-", TOKEN_OPERATOR);
	test_lexer("*", TOKEN_OPERATOR);
	test_lexer("/", TOKEN_OPERATOR);
	test_lexer("==", TOKEN_OPERATOR);
	test_lexer("!=", TOKEN_OPERATOR);

	// Test punctuators
	test_lexer(";", TOKEN_PUNCTUATOR);
	test_lexer(",", TOKEN_PUNCTUATOR);
	test_lexer("(", TOKEN_PUNCTUATOR);
	test_lexer(")", TOKEN_PUNCTUATOR);

	// Test errors
	test_lexer("@", TOKEN_ERROR);
	test_lexer("#", TOKEN_ERROR);
	test_lexer("`", TOKEN_ERROR);

	// Test EOF
	test_lexer("", TOKEN_EOF);

	return 0;
}
