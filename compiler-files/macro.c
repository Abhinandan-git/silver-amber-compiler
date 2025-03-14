#include "macro.h"

#include <stdlib.h>
#include <string.h>

static Macro *macro_table[HASH_SIZE]; // Hash table of macros

// Simple hash function
static unsigned int hash(const char *key)
{
	unsigned int hash = 0;
	while (*key)
	{
		hash = (hash * 1009) + *key++; // Prime number 1009 for better hashing
	}
	return hash % HASH_SIZE;
}

// Initialize macro table
void init_macro_table()
{
	memset(macro_table, 0, sizeof(macro_table));
}

// Insert a macro into the table
void insert_macro(const char *key, const char *value)
{
	unsigned int index = hash(key);
	Macro *new_macro = (Macro *)malloc(sizeof(Macro));
	new_macro->key = strdup(key);
	new_macro->value = strdup(value);
	new_macro->next = macro_table[index]; // Handle collisions via linked list
	macro_table[index] = new_macro;
}

// Get the value of a macro
const char *get_macro(const char *key)
{
	unsigned int index = hash(key);
	Macro *entry = macro_table[index];

	while (entry)
	{
		if (strcmp(entry->key, key) == 0)
		{
			return entry->value;
		}
		entry = entry->next;
	}
	// Return null if not found
	return NULL;
}

// Free memory used by macro table
void free_macro_table()
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		Macro *entry = macro_table[i];
		while (entry)
		{
			Macro *temp = entry;
			entry = entry->next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
		macro_table[i] = NULL;
	}
}
