#ifndef TABLES_H
#define TABLES_H

#define MAX_SYMBOL_LENGTH 15
#define MAX_SYMBOLS 10

typedef struct
{
	char lhs[MAX_SYMBOL_LENGTH];
	char rhs[MAX_SYMBOLS][MAX_SYMBOL_LENGTH];
	int rhs_count;
} Production;

extern Production *productions;

extern char **action_table;

extern int **goto_table;

#endif