#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

typedef enum
{
	COMPLETE,
	INCOMPLETE
} validity;

int main();

#include "preprocessor.h"
#include "macro.h"
#include "lexer.h"
#include "parser.h"

#endif