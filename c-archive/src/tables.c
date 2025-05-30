#include "tables.h"

char *non_terminals_names[16] = {
		"PROGRAM", "STATEMENTS", "STATEMENT", "FOR_LOOP", "IF_STMT", "FUNC_DEF", "FUNC_CALL", "ARGS", "BLOCK", "COND", "EXPR", "EXPR'", "OPRD", "COND_OPR", "OPR", "ASSGNMT"};

Productions productions[34] = {
		{"STATEMENTS", {"STATEMENT", "STATEMENTS"}, 2},
		{"STATEMENTS", {""}, 0},
		{"STATEMENT", {"FOR_LOOP"}, 1},
		{"STATEMENT", {"IF_STMT"}, 1},
		{"STATEMENT", {"FUNC_DEF"}, 1},
		{"STATEMENT", {"FUNC_CALL"}, 1},
		{"STATEMENT", {"EXPR"}, 1},
		{"STATEMENT", {"COND"}, 1},
		{"STATEMENT", {"ASSGNMT"}, 1},
		{"FOR_LOOP", {"for", "(", "IDENTIFIER ", "from", "OPRD", "to", "OPRD", "by", "OPRD", ")", "BLOCK"}, 11},
		{"IF_STMT", {"if", "(", "COND", ")", "BLOCK"}, 5},
		{"FUNC_DEF", {"function", "IDENTIFIER", "(", "ARGS", ")", "BLOCK"}, 6},
		{"FUNC_CALL", {"IDENTIFIER", "(", "ARGS", ")"}, 4},
		{"ARGS", {"IDENTIFIER", "ARGS"}, 2},
		{"ARGS", {""}, 0},
		{"BLOCK", {"{", "STATEMENTS", "}"}, 3},
		{"COND", {"EXPR", "COND_OPR", "EXPR"}, 3},
		{"EXPR", {"OPRD", "EXPR'"}, 2},
		{"EXPR'", {"OPR", "OPRD", "EXPR'"}, 3},
		{"EXPR'", {""}, 0},
		{"OPRD", {"LITERAL"}, 1},
		{"OPRD", {"IDENTIFIER"}, 1},
		{"COND_OPR", {"lt"}, 1},
		{"COND_OPR", {"gt"}, 1},
		{"COND_OPR", {"le"}, 1},
		{"COND_OPR", {"ge"}, 1},
		{"COND_OPR", {"eq"}, 1},
		{"COND_OPR", {"ne"}, 1},
		{"OPR", {"+"}, 1},
		{"OPR", {"-"}, 1},
		{"OPR", {"*"}, 1},
		{"OPR", {"/"}, 1},
		{"OPR", {"%"}, 1},
		{"ASSGNMT", {"IDENTIFIER", "=", "EXPR"}, 3}};

int state_table[150][16] = {
		{-1, 1, 2, 3, 4, 5, 6, -1, -1, 8, 7, -1, 14, -1, -1, 9},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, 16, 2, 3, 4, 5, 6, -1, -1, 8, 7, -1, 14, -1, -1, 9},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, 30, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 36, -1, 37, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 41, -1, 42, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, 37, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 49, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, 53, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 56, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 57, -1, -1, 58, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, 30, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 63, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, 67, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 69, -1, 70, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 73, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 75, -1, -1, 53, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, 77, 78, 79, 80, 81, 82, -1, -1, 84, 83, -1, 90, -1, -1, 85},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 92, -1, -1, 93, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 94, -1, -1, 58, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, 95, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 96, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, 100, 78, 79, 80, 81, 82, -1, -1, 84, 83, -1, 90, -1, -1, 85},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 101, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 107, -1, -1, 108, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 111, -1, 112, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, 115, 41, -1, 42, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, 117, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 118, -1, 112, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 119, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 122, -1, -1, 93, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 123, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 126, -1, -1, 127, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, 130, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 132, -1, -1, 108, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 134, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 135, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, 136, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, 139, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140, -1, -1, 127, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, 142, 78, 79, 80, 81, 82, -1, -1, 84, 83, -1, 90, -1, -1, 85},
		{-1, -1, -1, -1, -1, -1, -1, -1, 143, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 144, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 147, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, 149, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

char *action_table[150][25] = {
		{"s10", "err", "err", "err", "s11", "s12", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s15", "s13", "r2"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "acc"},
		{"s10", "err", "err", "err", "s11", "s12", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s15", "s13", "r2"},
		{"r3", "err", "err", "err", "r3", "r3", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r3", "r3", "r3"},
		{"r4", "err", "err", "err", "r4", "r4", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r4", "r4", "r4"},
		{"r5", "err", "err", "err", "r5", "r5", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r5", "r5", "r5"},
		{"r6", "err", "err", "err", "r6", "r6", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r6", "r6", "r6"},
		{"r7", "err", "err", "err", "r7", "r7", "err", "err", "err", "err", "s18", "s19", "s20", "s21", "s22", "s23", "err", "err", "err", "err", "err", "err", "r7", "r7", "r7"},
		{"r8", "err", "err", "err", "r8", "r8", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r8", "r8", "r8"},
		{"r9", "err", "err", "err", "r9", "r9", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r9", "r9", "r9"},
		{"err", "err", "err", "err", "err", "err", "s24", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "s25", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s26", "err"},
		{"r22", "err", "err", "err", "r22", "r22", "s27", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "s28", "r22", "r22", "r22"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "err", "r20", "r20", "r20", "r20", "r20", "r20", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "r20"},
		{"r21", "err", "err", "err", "r21", "r21", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r21", "r21", "r21", "r21", "r21", "err", "r21", "r21", "r21"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r1"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s15", "s38", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r23", "r23", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r24", "r24", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r25", "r25", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r26", "r26", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r27", "r27", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r28", "r28", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s39", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s43", "s44", "err"},
		{"err", "err", "err", "err", "err", "err", "s45", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r15", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s47", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s15", "s38", "err"},
		{"r18", "err", "err", "err", "r18", "r18", "err", "err", "err", "err", "r18", "r18", "r18", "r18", "r18", "r18", "err", "err", "err", "err", "err", "err", "r18", "r18", "r18"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s50", "s51", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r29", "r29", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r30", "r30", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r31", "r31", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r32", "r32", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r33", "r33", "err"},
		{"r17", "err", "err", "err", "r17", "r17", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r17", "r17", "r17"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "r20"},
		{"r22", "err", "err", "err", "r22", "r22", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "err", "r22", "r22", "r22"},
		{"err", "s54", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s55", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s18", "s19", "s20", "s21", "s22", "s23", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r20", "r20", "r20", "r20", "r20", "r20", "s31", "s32", "s33", "s34", "s35", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r15", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s47", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s60", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r15", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s47", "err"},
		{"r34", "err", "err", "err", "r34", "r34", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r34", "r34", "r34"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "err", "r20", "r20", "r20", "r20", "r20", "r20", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "r20"},
		{"r21", "err", "err", "err", "r21", "r21", "err", "err", "err", "err", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "err", "r21", "r21", "r21"},
		{"r22", "err", "err", "err", "r22", "r22", "err", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "err", "r22", "r22", "r22"},
		{"r18", "err", "err", "err", "r18", "r18", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r18", "r18", "r18"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s15", "s38", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s65", "s66", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "s68", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s71", "s72", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r18", "r18", "r18", "r18", "r18", "r18", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s43", "s44", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s74", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r13", "err", "err", "err", "r13", "r13", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r13", "r13", "r13"},
		{"err", "err", "err", "err", "err", "err", "err", "r14", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r19", "err", "err", "err", "r19", "r19", "err", "err", "err", "err", "r19", "r19", "r19", "r19", "r19", "r19", "err", "err", "err", "err", "err", "err", "r19", "r19", "r19"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "r20"},
		{"err", "err", "s76", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "r21", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "r22", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r11", "err", "err", "err", "r11", "r11", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r11", "r11", "r11"},
		{"s86", "err", "err", "err", "s87", "s88", "err", "err", "err", "r2", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s91", "s89", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r17", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r20", "err", "err", "err", "err", "err", "err", "err", "err", "s31", "s32", "s33", "s34", "s35", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r21", "err", "err", "err", "err", "err", "err", "err", "err", "r21", "r21", "r21", "r21", "r21", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r22", "err", "err", "err", "err", "err", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r20", "r20", "r20", "r20", "r20", "r20", "s31", "s32", "s33", "s34", "s35", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "s68", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r19", "err", "err", "err", "r19", "r19", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r19", "r19", "r19"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s97", "s98", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "s99", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"s86", "err", "err", "err", "s87", "s88", "err", "err", "err", "r2", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s91", "s89", "err"},
		{"r3", "err", "err", "err", "r3", "r3", "err", "err", "err", "r3", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r3", "r3", "err"},
		{"r4", "err", "err", "err", "r4", "r4", "err", "err", "err", "r4", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r4", "r4", "err"},
		{"r5", "err", "err", "err", "r5", "r5", "err", "err", "err", "r5", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r5", "r5", "err"},
		{"r6", "err", "err", "err", "r6", "r6", "err", "err", "err", "r6", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r6", "r6", "err"},
		{"r7", "err", "err", "err", "r7", "r7", "err", "err", "err", "r7", "s18", "s19", "s20", "s21", "s22", "s23", "err", "err", "err", "err", "err", "err", "r7", "r7", "err"},
		{"r8", "err", "err", "err", "r8", "r8", "err", "err", "err", "r8", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r8", "r8", "err"},
		{"r9", "err", "err", "err", "r9", "r9", "err", "err", "err", "r9", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r9", "r9", "err"},
		{"err", "err", "err", "err", "err", "err", "s102", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "s103", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s104", "err"},
		{"r22", "err", "err", "err", "r22", "r22", "s105", "err", "err", "r22", "err", "err", "err", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "s106", "r22", "r22", "err"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "r20", "r20", "r20", "r20", "r20", "r20", "r20", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "err"},
		{"r21", "err", "err", "err", "r21", "r21", "err", "err", "err", "r21", "err", "err", "err", "err", "err", "err", "r21", "r21", "r21", "r21", "r21", "err", "r21", "r21", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r18", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s71", "s72", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r19", "r19", "r19", "r19", "r19", "r19", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r12", "err", "err", "err", "r12", "r12", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r12", "r12", "r12"},
		{"err", "err", "err", "s110", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "r21", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "r22", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r16", "err", "err", "err", "r16", "r16", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r16", "r16", "r16"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "r1", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s91", "s113", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s114", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s43", "s44", "err"},
		{"err", "err", "err", "err", "err", "err", "s116", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r15", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s47", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s91", "s113", "err"},
		{"r18", "err", "err", "err", "r18", "r18", "err", "err", "err", "r18", "r18", "r18", "r18", "r18", "r18", "r18", "err", "err", "err", "err", "err", "err", "r18", "r18", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s120", "s121", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r20", "err", "err", "err", "err", "err", "err", "err", "err", "s31", "s32", "s33", "s34", "s35", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s124", "s125", "err"},
		{"r17", "err", "err", "err", "r17", "r17", "err", "err", "err", "r17", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r17", "r17", "err"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "r20", "err", "err", "err", "err", "err", "err", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "err"},
		{"r22", "err", "err", "err", "r22", "r22", "err", "err", "err", "r22", "err", "err", "err", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "err", "r22", "r22", "err"},
		{"err", "s128", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s129", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r15", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s47", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s131", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r34", "err", "err", "err", "r34", "r34", "err", "err", "err", "r34", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r34", "r34", "err"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "r20", "r20", "r20", "r20", "r20", "r20", "r20", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "err"},
		{"r21", "err", "err", "err", "r21", "r21", "err", "err", "err", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "r21", "err", "r21", "r21", "err"},
		{"r22", "err", "err", "err", "r22", "r22", "err", "err", "err", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "r22", "err", "r22", "r22", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r19", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s133", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r21", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "r22", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r18", "err", "err", "err", "r18", "r18", "err", "err", "err", "r18", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r18", "r18", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s91", "s113", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s65", "s66", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "s137", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s138", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r13", "err", "err", "err", "r13", "r13", "err", "err", "err", "r13", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r13", "r13", "err"},
		{"r19", "err", "err", "err", "r19", "r19", "err", "err", "err", "r19", "r19", "r19", "r19", "r19", "r19", "r19", "err", "err", "err", "err", "err", "err", "r19", "r19", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "s68", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r20", "err", "err", "err", "r20", "r20", "err", "err", "err", "r20", "err", "err", "err", "err", "err", "err", "s31", "s32", "s33", "s34", "s35", "err", "r20", "r20", "err"},
		{"err", "err", "s141", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r11", "err", "err", "err", "r11", "r11", "err", "err", "err", "r11", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r11", "r11", "err"},
		{"s86", "err", "err", "err", "s87", "s88", "err", "err", "err", "r2", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s91", "s89", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "s137", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r10", "err", "err", "err", "r10", "r10", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r10", "r10", "r10"},
		{"r19", "err", "err", "err", "r19", "r19", "err", "err", "err", "r19", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r19", "r19", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s97", "s98", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "s145", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r12", "err", "err", "err", "r12", "r12", "err", "err", "err", "r12", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r12", "r12", "err"},
		{"err", "err", "err", "s146", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r16", "err", "err", "err", "r16", "r16", "err", "err", "err", "r16", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r16", "r16", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "s124", "s125", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "s148", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"err", "err", "err", "err", "err", "err", "err", "err", "s137", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err"},
		{"r10", "err", "err", "err", "r10", "r10", "err", "err", "err", "r10", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "err", "r10", "r10", "err"},

};

int get_non_terminal_index(char *non_terminal)
{
	for (int idx = 0; idx < 16; idx++)
	{
		if (sizeof(non_terminals_names[idx]) == sizeof(non_terminal) && strcmp(non_terminals_names[idx], non_terminal) == 0)
		{
			return idx;
		}
	}
	return -1;
}