#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "main.h"

typedef enum
{
	TOKEN_EOF = 0,
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_STRING,
	TOKEN_KEYWORD,
	TOKEN_OPERATOR,
	TOKEN_PUNCTUATOR,
	TOKEN_ERROR
} TokenType;

typedef struct
{
	TokenType type;
	char *value;
	Token *next;
	Token *prev;
} Token;

validity init_lexer(const char *input_file);
void free_lexer();
Token *get_next_token();

#endif