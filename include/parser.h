#ifndef PARSER_H
#define PARSER_H

#include "main.h"
#include "tables.h"

void push(int);
int pop();
int peek();
validity parser(const char *);

#endif