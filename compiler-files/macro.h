#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include "main.h"

#define HASH_SIZE 100 // Define the size of the hash table

void init_macro_table();
void insert_macro(const char *key, const char *value);
const char *get_macro(const char *key);
void free_macro_table();

#endif