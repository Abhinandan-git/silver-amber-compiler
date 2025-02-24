#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For string methods

// Enumerating all the keywords
typedef enum {
	INTEGER,
	FLOATING,
	CHARACTER,
	STRING,
	FUNCTION,
	RETURN,
	EXIT
} TYPE_KEYWORD;

typedef enum {
	INTEGER_LITERAL
} TYPE_LITERAL;

// Generating structure for the keywords
typedef struct {
	TYPE_KEYWORD keyword;
} TOKEN_KEYWORD;

typedef struct {
	TYPE_LITERAL literal;
	int value;
} TOKEN_LITERAL;

// Function prototypes
void lexer(FILE *);

// Helper functions to get tokens
TOKEN_KEYWORD *generate_keyword(char, FILE *);
TOKEN_LITERAL *generate_number(char, FILE *);

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

		if (isdigit(current)) { // Literal starting found
			TOKEN_LITERAL *token = generate_number(current, file);

			printf("NUMBER FOUND: %d\n", token->value);
		} else if (isalpha(current)) { // Keyword starting found
			TOKEN_KEYWORD *token = generate_keyword(current, file);
			
			// Identify the token type
			switch (token->keyword) {
				case INTEGER:
					printf("TOKEN FOUND: %d\n", token->keyword);
					break;
				case FLOATING:
					printf("TOKEN FOUND: %d\n", token->keyword);
					break;
				case CHARACTER:
					printf("TOKEN FOUND: %d\n", token->keyword);
					break;
				case STRING:
					printf("TOKEN FOUND: %d\n", token->keyword);
					break;
				case FUNCTION:
					printf("TOKEN FOUND: %d\n", token->keyword);
					break;
				case RETURN:
					printf("TOKEN FOUND: %d\n", token->keyword);
					break;
				case EXIT:
					printf("TOKEN FOUND: %d\n", token->keyword);
					break;
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

	if (!strcmp(buffer, "integer")) {
		token->keyword = INTEGER;
	} else if (!strcmp(buffer, "floating")) {
		token->keyword = FLOATING;
	} else if (!strcmp(buffer, "character")) {
		token->keyword = CHARACTER;
	} else if (!strcmp(buffer, "string")) {
		token->keyword = STRING;
	} else if (!strcmp(buffer, "function")) {
		token->keyword = FUNCTION;
	} else if (!strcmp(buffer, "return")) {
		token->keyword = RETURN;
	} else if (!strcmp(buffer, "exit")) {
		token->keyword = EXIT;
	}

	fseek(file, -1, 1);
	return token;
}

TOKEN_LITERAL *generate_number(char current, FILE *file) {
	// Creating a literal token
	TOKEN_LITERAL *token = malloc(sizeof(TOKEN_LITERAL));

	int buffer[9] = {};
	int buffer_index = 0;
	int number = 0;

	// Store the characters recieved into a buffer
	do {
		buffer[buffer_index] = (current - '0');
		buffer_index++;
		
		current = fgetc(file);
	} while (current != EOF && isdigit(current));
	
	// Convert array to number
	for (int idx = 0; idx < buffer_index; idx++) {
		number = (number * 10) + buffer[idx];
	}

	// Assign the token values
	token->literal = INTEGER_LITERAL;
	token->value = number;

	fseek(file, -1, 1);
	return token;
}