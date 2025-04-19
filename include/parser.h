#ifndef PARSER_H
#define PARSER_H

#include "main.h"
#include "tables.h"
#include "lexerSymbolPipeline.h"

typedef enum
{
	ACTION_SHIFT,
	ACTION_REDUCE,
	ACTION_ACCEPT,
	ACTION_ERROR
} ActionType;

typedef struct
{
	ActionType type;
	int value; // For shift: target state; for reduce: production index
} ParsedAction;

typedef struct
{
	int state;
	char symbol[MAX_SYMBOL_LENGTH]; // Can be terminal or non-terminal
} StackEntry;

void push(int);
int pop();
int peek();
validity parser(const char *);

#endif