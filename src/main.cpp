#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

#include "generator.hpp"

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		std::cerr << "Incorrect usage of the command" << std::endl;
		std::cerr << "sacompiler <path_to_source_code.ffo>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string contents;
	{
		std::stringstream contents_stream;
		std::fstream input(argv[1], std::ios::in);
		contents_stream << input.rdbuf();
		contents = contents_stream.str();
	}

	Tokenizer tokenizer(std::move(contents));
	std::vector<Token> tokens = tokenizer.tokenize();

	Parser parser(std::move(tokens));
	std::optional<NodeExit> tree_root = parser.parse();

	if (!tree_root.has_value()) {
		std::cerr << "[MAIN] No exit found" << std::endl;
		exit(EXIT_FAILURE);
	}

	Generator generator(tree_root.value());	
	{
		std::fstream file("out.asm", std::ios::out);
		file << generator.generate();
	}

	return EXIT_SUCCESS;
}
