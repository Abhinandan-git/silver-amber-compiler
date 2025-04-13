#ifndef SYMBOL_H
#define SYMBOL_H

#define MAX_SYMBOL_NAME 64
#define SYMBOL_TABLE_SIZE 211

typedef enum {
	SYM_VARIABLE,
	SYM_FUNCTION,
	SYM_PARAMETER,
	SYM_TEMPORARY
} SymbolKind;

typedef enum {
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_BOOL,
	TYPE_VOID
} SymbolType;

typedef struct Symbol {
	char name[MAX_SYMBOL_NAME];
	SymbolKind kind;
	SymbolType type;
	int scope_level;

	struct Symbol* next; // For chaining (hash collisions)
} Symbol;

typedef struct {
	Symbol* table[SYMBOL_TABLE_SIZE];
} SymbolTable;

// Symbol table functions
SymbolTable* create_symbol_table();
void free_symbol_table(SymbolTable* symtab);
Symbol* insert_symbol(SymbolTable* symtab, const char* name, SymbolKind kind, SymbolType type, int scope_level);
Symbol* lookup_symbol(SymbolTable* symtab, const char* name, int scope_level);

#endif