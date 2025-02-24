#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For string methods

// Enumerating all the keywords
typedef enum
{
	INTEGER,
	FLOATING,
	CHARACTER,
	STRING,
	FUNCTION,
	RETURN,
	EXIT,
	UNKNOWN_KEYWORD
} TYPE_KEYWORD;

typedef enum
{
	INTEGER_LITERAL
} TYPE_LITERAL;

typedef enum
{
	COMMA,
	SEMICOLON,
	COLON,
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACE,
	RIGHT_BRACE,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	WHITESPACE,
	UNKNOWN
} TYPE_SEPARATOR;

// Generating structure for the keywords
typedef struct
{
	TYPE_KEYWORD keyword;
} TOKEN_KEYWORD;

typedef struct
{
	TYPE_LITERAL literal;
	int value;
} TOKEN_LITERAL;

typedef struct
{
	TYPE_SEPARATOR separator;
} TOKEN_SEPARATOR;

// Function prototypes
void lexer(FILE *);

// Helper functions to get tokens
TOKEN_KEYWORD *generate_keyword(char, FILE *);
TOKEN_LITERAL *generate_number(char, FILE *);
TOKEN_LITERAL *generate_seperator(char, FILE *);

int main()
{
	// Open the source file in read mode
	FILE *file;
	file = fopen("code.silv", "r");

	// If the file reading fails
	if (file == NULL)
	{
		printf("Reading file failed.");
		exit(EXIT_FAILURE);
	}

	// Call the lexer
	lexer(file);

	// Close the source file
	fclose(file);

	return 0;
}

void lexer(FILE *file)
{
	// Current character read from the source file
	char current;

	// Read through the entire source file
	do
	{
		current = fgetc(file);

		if (isdigit(current))
		{ // Literal starting found
			TOKEN_LITERAL *token = generate_number(current, file);
		}
		else if (isalpha(current))
		{ // Keyword starting found
			TOKEN_KEYWORD *token = generate_keyword(current, file);
		}
	} while (current != EOF);

	return;
}

TOKEN_KEYWORD *generate_keyword(char current, FILE *file)
{
	// Creating a keyword token
	TOKEN_KEYWORD *token = malloc(sizeof(TOKEN_KEYWORD));

	// If allocation fails
	if (token == NULL)
	{
		printf("Memory allocation failed.");
		exit(EXIT_FAILURE);
	}

	// Creating string buffer to store the keyword
	char buffer[32] = {0};
	int buffer_index = 0;

	do
	{
		buffer[buffer_index] = current;
		buffer_index++;

		// Get the latest character
		current = fgetc(file);
	} while (current != EOF && isalpha(current));

	// Terminating the buffer after reading is done
	buffer[buffer_index] = '\0';

	if (!strcmp(buffer, "integer"))
	{
		token->keyword = INTEGER;
	}
	else if (!strcmp(buffer, "float"))
	{
		token->keyword = FLOATING;
	}
	else if (!strcmp(buffer, "character"))
	{
		token->keyword = CHARACTER;
	}
	else if (!strcmp(buffer, "string"))
	{
		token->keyword = STRING;
	}
	else if (!strcmp(buffer, "function"))
	{
		token->keyword = FUNCTION;
	}
	else if (!strcmp(buffer, "return"))
	{
		token->keyword = RETURN;
	}
	else if (!strcmp(buffer, "exit"))
	{
		token->keyword = EXIT;
	}
	else
	{
		token->keyword = UNKNOWN_KEYWORD;
	}

	fseek(file, -1, SEEK_CUR);
	return token;
}

TOKEN_LITERAL *generate_number(char current, FILE *file)
{
	// Allocate memory for token
	TOKEN_LITERAL *token = malloc(sizeof(TOKEN_LITERAL));
	if (!token)
	{
		fprintf(stderr, "Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}

	char buffer[32] = {0};
	int buffer_index = 0;

	// Store digits in buffer
	do
	{
		// Prevent buffer overflow
		if (buffer_index < (sizeof(buffer) - 1))
		{
			buffer[buffer_index++] = current;
		}
		else
		{
			fprintf(stderr, "Error: Number too long!\n");
			free(token);
			return NULL;
		}
		current = fgetc(file);
	} while (current != EOF && isdigit(current));

	// Terminating the buffer after reading is done
	buffer[buffer_index] = '\0';

	// Convert buffer to integer
	token->value = atoi(buffer);
	token->literal = INTEGER_LITERAL;

	// If needed, move back one character
	if (current != EOF)
	{
		fseek(file, -1, SEEK_CUR);
	}

	return token;
}

TOKEN_SEPARATOR *generate_separator(char current, FILE *file)
{
	// Allocate memory for token
	TOKEN_SEPARATOR *token = malloc(sizeof(TOKEN_SEPARATOR));
	if (!token)
	{
		fprintf(stderr, "Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}

	// Identify the separator type
	switch (current)
	{
	case ',':
		token->separator = COMMA;
		break;
	case ';':
		token->separator = SEMICOLON;
		break;
	case ':':
		token->separator = COLON;
		break;
	case '(':
		token->separator = LEFT_PAREN;
		break;
	case ')':
		token->separator = RIGHT_PAREN;
		break;
	case '{':
		token->separator = LEFT_BRACE;
		break;
	case '}':
		token->separator = RIGHT_BRACE;
		break;
	case '[':
		token->separator = LEFT_BRACKET;
		break;
	case ']':
		token->separator = RIGHT_BRACKET;
		break;
	case ' ':
	case '\t':
	case '\n':
		token->separator = WHITESPACE;
		break;
	default:
		token->separator = UNKNOWN;
		fprintf(stderr, "Warning: Unknown separator '%c'\n", current);
		break;
	}

	return token;
}