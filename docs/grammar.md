# Grammar for the Language

---

- program        → top_level_list
- top_level_list → top_level top_level_list | ε
- top_level      → declaration | function

---

- function       → type identifier "(" param_list_opt ")" block

---

- param_list_opt → param_list | ε
- param_list     → parameter param_list_tail
- param_list_tail → "," parameter param_list_tail | ε
- parameter      → type identifier

---

- declaration    → type pointer_opt identifier init_opt ";"
- init_opt       → "=" expression | ε
- pointer_opt    → "*" | ε

---

- block          → "{" statement_list "}"
- statement_list → statement statement_list | ε

---

- statement      → declaration
                 | assignment ";"
                 | if_statement
                 | while_loop
                 | for_loop
                 | return_statement
                 | expression ";"
                 | block

---

- assignment     → pointer_opt identifier "=" expression

---

- if_statement   → "if" "(" expression ")" statement elseif_list else_opt
- elseif_list    → elseif_clause elseif_list | ε
- elseif_clause  → "elseif" "(" expression ")" statement
- else_opt       → "else" statement | ε

---

- while_loop     → "while" "(" expression ")" statement

---

- for_loop       → "for" "(" for_init_opt ";" expression_opt ";" expression_opt ")" statement
- for_init_opt   → declaration | assignment | ε
- expression_opt → expression | ε

---

- return_statement → "return" expression_opt ";"

---

- expression     → term expression_tail
- expression_tail→ binary_op term expression_tail | ε
- term           → unary_op term
                 | "(" expression ")"
                 | function_call
                 | pointer_opt identifier
                 | string_literal
                 | boolean_literal
                 | char_literal
                 | number

---

- function_call  → identifier "(" argument_list_opt ")"
- argument_list_opt → argument_list | ε
- argument_list  → expression argument_list_tail
- argument_list_tail → "," expression argument_list_tail | ε

---

- binary_op      → "+" | "-" | "*" | "/" 
                 | "==" | "!=" | "" | "" | "=" | "=" 
                 | "&&" | "||" | "="

---

- unary_op       → "!" | "-" | "&" | "*"

---

- type           → "integer" | "floating" | "character" | "boolean" | "string"

---

- boolean_literal→ "true" | "false"
- char_literal   → "'" any_char "'"
- string_literal → "\"" string_characters "\""

---

- identifier     → [a-zA-Z_][a-zA-Z0-9_]*
- number         → [0-9]+ ("." [0-9]+)?

---