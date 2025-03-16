#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

#include "main.h"

#define BUFFER_SIZE 1024

validity preprocessor(const char *, const char *);
validity write_header_file(char *, FILE *);
validity get_macro_definition(char *);

#endif