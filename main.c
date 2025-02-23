#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h> // For string methods
#include <ctype.h>

// Enumerating all the keywords
typedef enum {
	INTEGER,
	FLOATING,
	CHARACTER,
	STRING,
	FUNCTION,
	RETURN,
	EXIT,
} TYPE_KEYWORD;

// Generating structure for the keywords
typedef struct {
	TYPE_KEYWORD keyword;
} TOKEN_KEYWORD;

// Functions prototypes
void lexer(FILE *);

// Helper functions to get tokens
TOKEN_KEYWORD *generate_keyword(char, FILE *);

int main() {
	// Open the source file in read mode
	FILE *file;
	file = fopen("code.silv", "r");

	// If the file reading fails
	if (file == NULL) {
		printf("Reading file failed.");
		return 1;
	}

	// Call the lexer
	lexer(file);

	// Close the source file
	fclose(file);

	return 0;
}

void lexer(FILE *file)  {
	// Current character read from the source file
	char current;
	
	// Read through the entire source file
	do {
		current = fgetc(file);

		if (isalpha(current)) {
			TOKEN_KEYWORD *token = generate_keyword(current, file);
			if (token->keyword == EXIT) {
				printf("TOKEN FOUND: EXIT\n");
			}
		}
	} while (current != EOF);

	return;
}

TOKEN_KEYWORD *generate_keyword(char current, FILE *file) {
	// Creating a keyword token
	TOKEN_KEYWORD *token = malloc(sizeof(TOKEN_KEYWORD));
	
	// Creating string buffer to store the keyword
	char buffer[10] = {};
	int buffer_index = 0;

	do {
		buffer[buffer_index] = current;
		buffer_index++;

		printf("CHARACTER FOUND: %c\n", current);

		// Get the latest character
		current = fgetc(file);
	} while (current != EOF && isalpha(current));

	if (!strcmp(buffer, "exit")) {
		token->keyword = EXIT;
	}

	return token;
}