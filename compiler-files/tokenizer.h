#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "main.h"

Token *create_token(TokenType, const char *);
int is_keyword(const char *);
int is_operator(const char *);
int is_punctuator(const char *);
Token *compare_buffer(char *, int);

#endif