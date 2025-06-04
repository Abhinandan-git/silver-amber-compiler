# Silver Amber Compiler

**Silver Amber Compiler** is a custom compiler written in modern C++ for a new experimental programming language called **FFO**. It is a ground-up implementation featuring a handcrafted lexer, and a backend for generating and executing native machine code—all without relying on traditional compiler tools like Flex or Bison.

This repository is the core of a broader DevOps-based online compiler project.

---

## ✨ Key Features

* 🔤 **Lexical Analysis** – Custom-built lexer to tokenize FFO source code.
* 🧠 **Syntax Analysis** – Parsing tokens into a syntactic structure.
* 🌳 **AST Support** – Parses tokens into an Abstract Syntax Tree for easier processing.
* ⚙️ **Code Generation** – Converts AST into machine-executable code.
* 🚫 **No Dependencies** – Pure C++ implementation without Flex, Bison, or external libs.
* 🧪 **Testable Backend** – Easily embeddable in DevOps workflows for automated execution.

---

## 📁 Project Structure

```
silver-amber-compiler/
├── c-archive/               # Old compiler written in C
├── src/
│   ├── main.cpp             # Compiler entry point
│   ├── tokenization.hpp     # Lexer implementation
│   ├── parser.hpp           # CLR(1) parser
│   ├── generation.hpp       # Code generation logic
│   ├── arena.hpp            # Memory arena for efficient allocation
├── docs/
│   └── grammar.md           # FFO language grammar and syntax rules
├── build/                   # Build output directory
├── LICENSE
└── README.md
```

---

## 🛠️ Installation & Build

### Prerequisites

* GCC/G++ (C++20 or later)
* Linux (tested on Ubuntu 24.04.2)
* NASM (for assembly)
* ld linker (converting the output into executable)
* CMake

### Build Instructions

```bash
git clone https://github.com/abhinandan-git/silver-amber-compiler.git
cd silver-amber-compiler

# Basic build (manual)
g++ -std=c++20 -O2 -o build/sacompiler src/main.cpp

# OR use CMake
# mkdir build && cd build
# cmake ..
# make
```

---

## 🚀 Usage

Compile a source file written in FFO:

```bash
./build/sacompiler path/to/source.ffo
```

Output will be printed to stdout or executed, depending on the source and generation logic.

---

## 📌 Development Roadmap

| Feature                     | Status         |
| --------------------------- | -------------- |
| Custom Lexer                | ✅ Completed   |
| CLR(1) Parser               | ✅ Completed   |
| Abstract Syntax Tree        | ✅ Completed   |
| Code Generation             | ✅ Completed   |
| CI/CD Integration           | ✅ Completed   |

---

## 🤝 Contributing

We welcome contributions and ideas! Please follow these steps:

1. Fork the repository
2. Create a new branch (`git checkout -b feature-xyz`)
3. Commit your changes
4. Push to your fork
5. Open a Pull Request

You can also open Issues to suggest features, report bugs, or request enhancements.

---

## 🪪 License

This project is licensed under the **GNU General Public License v3.0**.
See the [`LICENSE`](./LICENSE) file for details.

---

## 📚 Additional Notes

* This compiler is a component of a larger DevOps-based online compiler system.
* All execution is sandboxed using Docker containers in production deployments.