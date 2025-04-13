#include "symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int hash(const char *str)
{
	unsigned int hash = 0;
	while (*str)
		hash = (hash << 2) ^ *str++;
	return hash % SYMBOL_TABLE_SIZE;
}

SymbolTable *create_symbol_table()
{
	SymbolTable *symbol_table = malloc(sizeof(SymbolTable));
	if (!symbol_table)
	{
		fprintf(stderr, "Out of memory creating symbol table\n");
		exit(1);
	}
	memset(symbol_table->table, 0, sizeof(symbol_table->table));
	return symbol_table;
}

void free_symbol_table(SymbolTable *symbol_table)
{
	for (int i = 0; i < SYMBOL_TABLE_SIZE; ++i)
	{
		Symbol *symbol = symbol_table->table[i];
		while (symbol)
		{
			Symbol *next = symbol->next;
			free(symbol);
			symbol = next;
		}
	}
	free(symbol_table);
}

Symbol *insert_symbol(SymbolTable *symbol_table, const char *name, SymbolKind kind, SymbolType type, int scope_level)
{
	unsigned int index = hash(name);
	Symbol *symbol = symbol_table->table[index];

	while (symbol)
	{
		if (strcmp(symbol->name, name) == 0 && symbol->scope_level == scope_level)
		{
			// Already declared in this scope
			return NULL;
		}
		symbol = symbol->next;
	}

	symbol = malloc(sizeof(Symbol));
	strncpy(symbol->name, name, MAX_SYMBOL_NAME);
	symbol->kind = kind;
	symbol->type = type;
	symbol->scope_level = scope_level;
	symbol->next = symbol_table->table[index];
	symbol_table->table[index] = symbol;

	return symbol;
}

Symbol *lookup_symbol(SymbolTable *symbol_table, const char *name, int scope_level)
{
	unsigned int index = hash(name);
	Symbol *symbol = symbol_table->table[index];
	while (symbol)
	{
		if (strcmp(symbol->name, name) == 0 && symbol->scope_level <= scope_level)
		{
			return symbol;
		}
		symbol = symbol->next;
	}
	return NULL;
}
