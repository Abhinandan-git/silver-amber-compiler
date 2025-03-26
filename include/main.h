#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define STACK_SIZE 256

typedef enum
{
	COMPLETE,
	INCOMPLETE
} validity;

typedef struct Macro
{
	char *key;					// Macro name
	char *value;				// Macro replacement
	struct Macro *next; // Linked list (for handling collisions)
} Macro;

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

typedef struct Token
{
	TokenType type;
	char *value;
} Token;

typedef struct
{
	int state;
	Token token;
} StackElement;

typedef struct
{
	StackElement items[STACK_SIZE];
	int top;
} ParserStack;

int main();

#include "preprocessor.h"
#include "lexer.h"
#include "tokenizer.h"
#include "macro.h"

#endif