# Crafting Interpreters - Lox Language Implementations

This repository contains implementations of the **Lox** programming language from [Crafting Interpreters](https://craftinginterpreters.com/) by Robert Nystrom.

## What is Lox?

Lox is a dynamically-typed scripting language designed to teach interpreter design. It includes features like:
- Variables, functions, and classes
- Control flow (if/else, for, while, break)
- Closures and first-class functions
- Object-oriented programming with inheritance
- Dynamic typing and garbage collection

## Two Implementations

### jlox - Tree-Walk Interpreter (Java)
Located in: `Book/com/craftinginterpreters/lox/`

A tree-walk interpreter that directly executes the abstract syntax tree (AST). Each node is evaluated as the tree is traversed.

**Key files:**
- `Scanner.java` - Lexical analysis (tokenization)
- `Parser.java` - Syntax analysis (builds AST)
- `Interpreter.java` - AST evaluation and execution
- `Resolver.java` - Variable resolution and scope analysis
- `Environment.java` - Runtime environment/scope management
- `Expr.java` / `Stmt.java` - AST node definitions

**Features implemented:**
- ✅ Expressions (arithmetic, logical, comparisons)
- ✅ Variables and assignments
- ✅ Functions and closures
- ✅ Classes and inheritance
- ✅ Control flow (if/else, for, while, break)
- ✅ Extension methods
- ✅ Getter methods
- ✅ Class methods (static methods)

### clox - Bytecode Virtual Machine (C)
Located in: `c/` and `craftinginterpreters/c/`

A bytecode compiler and virtual machine that compiles Lox to bytecode, then executes it on a stack-based VM. Much faster than jlox.

**Key files:**
- `scanner.c/.h` - Lexical analysis
- `compiler.c/.h` - Bytecode compilation
- `vm.c/.h` - Virtual machine execution
- `chunk.c/.h` - Bytecode chunk management
- `value.c/.h` - Runtime values
- `table.c/.h` - Hash table implementation
- `object.c/.h` - Object representation
- `memory.c/.h` - Memory management with GC

## Following the Book

This project follows the progression of "Crafting Interpreters":

1. **Part I: jlox (Java Tree-Walk Interpreter)**
   - Chapters 1-13: Core language features
   - Chapter 8: Statements and State
   - Chapter 9: Control Flow
   - Chapter 10: Functions
   - Chapter 11: Resolving and Binding
   - Chapter 12: Classes
   - Chapter 13: Inheritance
   - **Challenge Questions**: Custom features added (getters, class methods, extensions)

2. **Part II: clox (C Bytecode VM)**
   - Chapters 14-30: Bytecode compilation and optimization
   - Chapter 14: Chunks of Bytecode
   - Efficient line number tracking (challenge question 1)
   - Modern VM architecture and optimization


