# Grammer for the language

| Non-Terminal | **First** | **Follow** |
|-|-|-|
| **S'**| `{ program }` | `{ $ }` |
| **program** | `{ statement_list }` | `{ $ }` |
| **statement_list** | `{ statement, ε }` | `{ '}' , $ }` |
| **statement** | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', NUMBER, STRING, 'true', 'false', 'null', '!' , '-' }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-', $ }` |
| **assignment** | `{ IDENTIFIER }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **if_statement** | `{ 'if' }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **while_loop** | `{ 'while' }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **for_loop** | `{ 'for' }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **function_declaration** | `{ 'function' }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **function_call** | `{ IDENTIFIER }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **return_statement** | `{ 'return' }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **expression_statement** | `{ expression }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **block** | `{ '{' }` | `{ IDENTIFIER, 'if', 'while', 'for', 'function', 'return', '{', ';', '}', NUMBER, STRING, 'true', 'false', 'null', '!', '-' }` |
| **expression** | `{ logical_or }` | `{ ';', ')', ',' }`|
| **logical_or** | `{ logical_and }` | `{ ';', ')', ',' }`|
| **logical_and** | `{ equality }` | `{ '\|\|', ';', ')', ',' }` |
| **equality** | `{ comparison }` | `{ '&&', '\|\|', ';', ')', ',' }` |
| **comparison** | `{ term }` | `{ '==', '!=', '&&', '\|\|', ';', ')', ',' }` |
| **term** | `{ factor }` | `{ '<', '>', '<=', '>=', '==', '!=', '&&', '\|\|', ';', ')', ',' }` |
| **factor** | `{ unary }` | `{ '+', '-', '<', '>', '<=', '>=', '==', '!=', '&&', '\|\|', ';', ')', ',' }` |
| **unary** | `{ '!', '-', primary }` | `{ '*', '/', '+', '-', '<', '>', '<=', '>=', '==', '!=', '&&', '\|\|', ';', ')', ',' }` |
| **primary** | `{ IDENTIFIER, NUMBER, STRING, 'true', 'false', 'null', '(', expression ')' }` | `{ '*', '/', '+', '-', '<', '>', '<=', '>=', '==', '!=', '&&', '\|\|', ';', ')', ',' }` |
| **parameter_list** | `{ IDENTIFIER }` | `{ ')' }` |
| **argument_list** | `{ expression }` | `{ ')' }` |
