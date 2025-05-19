#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "main.h"

Token *create_token(TokenType, char *);
Token *compare_buffer(char *, int);

#endif