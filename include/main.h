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

typedef enum {
	SYMBOL_SEMICOLON,     // ;
	SYMBOL_STATIC,        // static
	SYMBOL_COMMA,         // ,
	SYMBOL_ID,            // identifier
	SYMBOL_LBRACKET,      // [
	SYMBOL_NUMCONST,      // numeric constant
	SYMBOL_RBRACKET,      // ]
	SYMBOL_INTEGER,       // integer
	SYMBOL_BOOLEAN,       // boolean
	SYMBOL_CHARACTER,     // character
	SYMBOL_LPAREN,        // (
	SYMBOL_RPAREN,        // )
	SYMBOL_LBRACE,        // {
	SYMBOL_RBRACE,        // }
	SYMBOL_IF,            // if
	SYMBOL_THEN,          // then
	SYMBOL_WHILE,         // while
	SYMBOL_DO,            // do
	SYMBOL_FOR,           // for
	SYMBOL_ASSIGN,        // =
	SYMBOL_TO,            // to
	SYMBOL_RETURN,        // return
	SYMBOL_BREAK,         // break
	SYMBOL_OR,            // or
	SYMBOL_AND,           // and
	SYMBOL_NOT,           // not
	SYMBOL_LE,            // <=
	SYMBOL_LT,            // <
	SYMBOL_GT,            // >
	SYMBOL_GE,            // >=
	SYMBOL_EQ,            // ==
	SYMBOL_NEQ,           // !=
	SYMBOL_MINMAXOP,      // minmaxop (e.g., :>: or :<:)
	SYMBOL_PLUS,          // +
	SYMBOL_MINUS,         // −
	SYMBOL_MULT,          // ∗
	SYMBOL_DIV,           // /
	SYMBOL_MOD,           // %
	SYMBOL_QUESTION,      // ?
	SYMBOL_CHARCONST,     // character constant
	SYMBOL_STRINGCONST,   // string constant
	SYMBOL_TRUE,          // true
	SYMBOL_FALSE,         // false
	SYMBOL_DOLLAR,        // $
	SYMBOL_ERROR          // error or unknown token
} Symbol;

typedef struct {
	char* lexeme;
	Symbol symbol;
} LexemeSymbolMap;

int main();

#include "preprocessor.h"
#include "lexer.h"
#include "parser.h"
#include "tokenizer.h"
#include "macro.h"
#include "tables.h"

#endif