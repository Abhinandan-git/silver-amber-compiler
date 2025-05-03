#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define STACK_SIZE 1024

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
	// Keywords
	TOKEN_FOR = 0,
	TOKEN_FROM,
	TOKEN_TO,
	TOKEN_BY,

	TOKEN_IF,

	TOKEN_FUNCTION,

	TOKEN_LP,
	TOKEN_RP,
	TOKEN_LB,
	TOKEN_RB,

	TOKEN_LT,
	TOKEN_GT,
	TOKEN_LE,
	TOKEN_GE,
	TOKEN_EQ,
	TOKEN_NE,
	
	TOKEN_PL,
	TOKEN_MI,
	TOKEN_MU,
	TOKEN_DI,
	TOKEN_MO,
	
	TOKEN_AS,

	TOKEN_LITERAL,
	TOKEN_IDENTIFIER,

	TOKEN_EOF,
	TOKEN_ERROR
} TokenType;

typedef struct Token
{
	TokenType type;
	char *value;
} Token;

int main();

#include "preprocessor.h"
#include "lexer.h"
#include "tokenizer.h"
#include "macro.h"
#include "parser.h"

#endif