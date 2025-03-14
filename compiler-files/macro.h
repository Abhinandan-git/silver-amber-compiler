#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>

#define HASH_SIZE 100 // Define the size of the hash table

typedef struct Macro
{
	char *key;					// Macro name
	char *value;				// Macro replacement
	struct Macro *next; // Linked list (for handling collisions)
} Macro;

void init_macro_table();
void insert_macro(const char *key, const char *value);
const char *get_macro(const char *key);
void free_macro_table();

#endif