#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "main.h"

TOKEN *create_token(TokenType, const char *);
int is_keyword(const char *);
int is_operator(const char *);
int is_punctuator(const char *);
TOKEN *compare_buffer(char *, int);

#endif