#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include "generator.hpp"

int main(int argc, char const *argv[]) {
	// Check if the source file is included while calling the compiler
	if (argc != 2) { // First argument is always the name of the file
		// Give error on invalid usage
		std::cerr << "Incorrect usage of the command" << std::endl;
		std::cerr << "sacompiler <path_to_source_code.ffo>" << std::endl;
		return EXIT_FAILURE; // Macro
	}

	// Get entire file as the string
	std::string contents;
	{
		// Local-scoped to destruct input streams
		std::stringstream contents_stream;
		std::fstream input(argv[1], std::ios::in); // Open file mentioned as argument
		// Read the file into a buffer
		contents_stream << input.rdbuf(); // rdbuf is read_buffer
		// Feed the buffer format into string
		contents = contents_stream.str(); // Convert the sstream to string
	}

	// Move the content into the tokenizer
	Tokenizer tokenizer(std::move(contents)); // Move the pointer to class contructor
	std::vector<Token> tokens = tokenizer.tokenize(); // Returns tokens based on the file

	// Move the tokens generated into the parser
	Parser parser(std::move(tokens)); // Move tokens pointer to class constructor
	std::optional<NodeExit> tree_root = parser.parse(); // Null in case of an error

	// Check for error in the tree
	if (!tree_root.has_value()) {
		std::cerr << "[MAIN] No exit (node) found" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Pass the Abstract Syntax Tree generated into the code generator
	Generator generator(tree_root.value());	
	{
		// Local-scoped output assembly file
		std::fstream file("out.asm", std::ios::out); // Open file for writing
		file << generator.generate(); // Generate intermediate code
	}

	return EXIT_SUCCESS; // Macro
}
