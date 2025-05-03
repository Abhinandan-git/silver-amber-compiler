#ifndef TABLES_H
#define TABLES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char *non_terminal;
	char *production[25];
	int production_size;
} Productions;

extern char *non_terminals[16];
extern Productions productions[34];
extern int state_table[][16];
extern char *action_table[][25];

int get_non_terminal_index(char *);

#endif