# Silver Amber Compiler

Silver Amber Compiler is a custom compiler for the FFO programming language, implemented entirely in C. This project aims to create a fully functional compiler, including lexical analysis (lexer), parsing (LR(1) or LALR(1) parser), and code generation, without using external tools like Flex or Bison.

## Features
- **Lexical Analysis**: Converts source code into tokens using a custom lexer.
- **Parsing**: Implements an LR(1) or LALR(1) parser for syntax analysis.
- **Compilation**: Translates FFO code into executable machine code.
- **Custom Language Design**: FFO is a new programming language being developed for this project.
- **Implemented in C**: No external dependencies or compiler generators.

## Project Structure
```
silver-amber-compiler/
├── src/               # Source files
│   ├── lexer.c        # Lexer implementation
│   ├── parser.c       # Parser implementation
│   ├── main.c         # Compiler entry point
│   ├── codegen.c      # Code generation (future implementation)
├── include/           # Header files
│   ├── lexer.h
│   ├── parser.h
│   ├── codegen.h
├── build/             # Compiled objects and binary output
├── Makefile           # Build system configuration
├── README.md          # Project documentation
```

## Installation & Building
### **Prerequisites**
- GCC (or any C compiler)
- `make` (for automated build)

### **Build Instructions**
1. Clone the repository:
   ```sh
   git clone https://github.com/abhinandan-git/silver-amber-compiler.git
   cd silver-amber-compiler
   ```
2. Compile the project:
   ```sh
   make
   ```
3. Run the compiler:
   ```sh
   ./build/ffo-compiler <source_file.ffo>
   ```

## Usage
To compile an `.ffo` source file:
```sh
./build/ffo-compiler example.ffo
```

## Development Roadmap
- ✅ Implement Lexer (Tokenization)
- ⏳ Implement LR(1) / LALR(1) Parser
- ⏳ Implement Abstract Syntax Tree (AST)
- ⏳ Implement Semantic Analysis
- ⏳ Code Generation
- ⏳ Optimization & Testing

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests.

## License
This project is licensed under the GNU General Public license. See `LICENSE` for details.