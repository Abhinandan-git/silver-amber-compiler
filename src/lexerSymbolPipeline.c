#include <string.h>
#include "main.h"

Symbol map_token_to_symbol(TokenType type, const char *lexeme)
{
	if (type == TOKEN_IDENTIFIER)
		return SYMBOL_ID;
	if (type == TOKEN_NUMBER)
		return SYMBOL_NUMCONST;
	if (type == TOKEN_STRING)
		return SYMBOL_STRINGCONST;
	if (type == TOKEN_ERROR)
		return SYMBOL_ERROR;
	if (type == TOKEN_EOF)
		return SYMBOL_DOLLAR;

	if (type == TOKEN_KEYWORD)
	{
		if (strcmp(lexeme, "if") == 0)
			return SYMBOL_IF;
		if (strcmp(lexeme, "then") == 0)
			return SYMBOL_THEN;
		if (strcmp(lexeme, "while") == 0)
			return SYMBOL_WHILE;
		if (strcmp(lexeme, "do") == 0)
			return SYMBOL_DO;
		if (strcmp(lexeme, "for") == 0)
			return SYMBOL_FOR;
		if (strcmp(lexeme, "return") == 0)
			return SYMBOL_RETURN;
		if (strcmp(lexeme, "break") == 0)
			return SYMBOL_BREAK;
		if (strcmp(lexeme, "or") == 0)
			return SYMBOL_OR;
		if (strcmp(lexeme, "and") == 0)
			return SYMBOL_AND;
		if (strcmp(lexeme, "not") == 0)
			return SYMBOL_NOT;
		if (strcmp(lexeme, "static") == 0)
			return SYMBOL_STATIC;
		if (strcmp(lexeme, "integer") == 0)
			return SYMBOL_INTEGER;
		if (strcmp(lexeme, "boolean") == 0)
			return SYMBOL_BOOLEAN;
		if (strcmp(lexeme, "character") == 0)
			return SYMBOL_CHARACTER;
		if (strcmp(lexeme, "to") == 0)
			return SYMBOL_TO;
		if (strcmp(lexeme, "true") == 0)
			return SYMBOL_TRUE;
		if (strcmp(lexeme, "false") == 0)
			return SYMBOL_FALSE;
	}

	if (type == TOKEN_OPERATOR)
	{
		if (strcmp(lexeme, "+") == 0)
			return SYMBOL_PLUS;
		if (strcmp(lexeme, "-") == 0)
			return SYMBOL_MINUS;
		if (strcmp(lexeme, "*") == 0)
			return SYMBOL_MULT;
		if (strcmp(lexeme, "/") == 0)
			return SYMBOL_DIV;
		if (strcmp(lexeme, "%") == 0)
			return SYMBOL_MOD;
		if (strcmp(lexeme, "=") == 0)
			return SYMBOL_ASSIGN;
		if (strcmp(lexeme, "<") == 0)
			return SYMBOL_LT;
		if (strcmp(lexeme, "<=") == 0)
			return SYMBOL_LE;
		if (strcmp(lexeme, ">") == 0)
			return SYMBOL_GT;
		if (strcmp(lexeme, ">=") == 0)
			return SYMBOL_GE;
		if (strcmp(lexeme, "==") == 0)
			return SYMBOL_EQ;
		if (strcmp(lexeme, "!=") == 0)
			return SYMBOL_NEQ;
		if (strcmp(lexeme, ":<:") == 0 || strcmp(lexeme, ":>:") == 0)
			return SYMBOL_MINMAXOP;
		if (strcmp(lexeme, "?") == 0)
			return SYMBOL_QUESTION;
	}

	if (type == TOKEN_PUNCTUATOR)
	{
		if (strcmp(lexeme, ";") == 0)
			return SYMBOL_SEMICOLON;
		if (strcmp(lexeme, ",") == 0)
			return SYMBOL_COMMA;
		if (strcmp(lexeme, "(") == 0)
			return SYMBOL_LPAREN;
		if (strcmp(lexeme, ")") == 0)
			return SYMBOL_RPAREN;
		if (strcmp(lexeme, "[") == 0)
			return SYMBOL_LBRACKET;
		if (strcmp(lexeme, "]") == 0)
			return SYMBOL_RBRACKET;
		if (strcmp(lexeme, "{") == 0)
			return SYMBOL_LBRACE;
		if (strcmp(lexeme, "}") == 0)
			return SYMBOL_RBRACE;
	}

	// If no symbol matches, return ERROR
	return SYMBOL_ERROR;
}
