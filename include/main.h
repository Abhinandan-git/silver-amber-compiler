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
	// Special
	TOKEN_EOF = 0,
	TOKEN_ERROR,

	// Identifiers & Literals
	TOKEN_IDENTIFIER,
	TOKEN_INTEGER,
	TOKEN_FLOAT,

	// Keywords
	TOKEN_FOR,
	TOKEN_FROM,
	TOKEN_TO,
	TOKEN_BY,
	TOKEN_IF,
	TOKEN_FUNCTION,

	// Condition Operators
	TOKEN_LT, // lt
	TOKEN_GT, // gt
	TOKEN_LE, // le
	TOKEN_GE, // ge
	TOKEN_EQ, // eq
	TOKEN_NE, // ne

	// Arithmetic Operators
	TOKEN_PLUS,	 // +
	TOKEN_MINUS, // -
	TOKEN_STAR,	 // *
	TOKEN_SLASH, // /

	// Assignment
	TOKEN_ASSIGN, // =

	// Punctuation
	TOKEN_LPAREN, // (
	TOKEN_RPAREN, // )
	TOKEN_LBRACE, // {
	TOKEN_RBRACE, // }
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

#endif