#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"

#define ACTION_SHIFT 's'
#define ACTION_REDUCE 'r'
#define ACTION_ACCEPT 'a'
#define ACTION_ERROR 'e'

void push_state(const int);
int peek_state();
void pop_state();
void push_lexeme(const char *);
char *peek_lexeme();
void pop_lexeme();
void reduce_by_rule(int);
validity parser(const char *);

#endif
