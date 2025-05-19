#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "main.h"

validity init_lexer(const char *input_file);
Token *peek_token();
Token *get_next_token();
void free_lexer();

#endif