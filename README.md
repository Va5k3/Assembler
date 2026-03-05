# Assembler (Hack / nand2tetris)

A small assembler for the **Hack computer** from the *nand2tetris* course.

This project is written in C++ and includes a simple **wxWidgets GUI** that lets you paste / open `.asm` files, assemble them, and save the resulting `.hack` machine code.

> Note: This is a student project I built while working through nand2tetris. The code and comments are kept close to the way I originally wrote them.

## Features

- Translates Hack assembly (`.asm`) to Hack machine code (`.hack`)
- Two-pass approach
  - **Pass 1:** reads labels and resolves ROM addresses
  - **Pass 2:** encodes A/C instructions and allocates variables
- Symbol table support
  - Predefined symbols (`SP`, `LCL`, `ARG`, `THIS`, `THAT`, `R0`..`R15`, `SCREEN`, `KBD`)
  - User-defined labels `(LOOP)`
  - User-defined variables (allocated starting at RAM[16])
- GUI workflow
  - open a file or type code
  - assemble
  - preview output
  - save output
  - shows a symbol table dump (`SymbolTable.txt`)

## How it works (high level)

The assembly pipeline lives in `Assembler.cpp` and roughly looks like this:

1. **Input cleanup** (`Assembler::asmEdit`)
   - strips comments (`// ...`)
   - removes spaces
   - pushes non-empty lines into a queue
2. **First pass** (`Assembler::firstPass`)
   - detects label declarations like `(LOOP)`
   - stores label -> ROM address in the symbol table
   - produces a second queue without label lines
3. **Second pass** (`Assembler::secondPass`)
   - parses each instruction using `Parser::parseInst`
   - writes 16-bit machine code lines into the output file

### A-instructions

- `@123` is encoded as: `0` + 15-bit value
- `@symbol` is resolved using the symbol table
  - predefined symbols are already present
  - new variables are allocated starting from RAM address 16

### C-instructions

C-instructions are encoded as:

- `111` + `comp` (7 bits) + `dest` (3 bits) + `jump` (3 bits)

The lookup tables for `comp`, `dest` and `jump` live in `Parser.cpp`.

## Project structure

- `Assembler.*` — two-pass assembler and file pipeline
- `Parser.*` — parses A/C instructions, contains comp/dest/jump dictionaries
- `SymbolTable.*` — predefined symbols + label/variable management
- `MainFrame.*`, `App.*` — wxWidgets GUI entry point
- `testAsm/` — small example programs used for manual testing

## Building / running

This repo contains a Visual Studio project (`V45k3 - Assembler.vcxproj`).

General steps (Windows / Visual Studio):

1. Open the `.vcxproj` in Visual Studio
2. Make sure **wxWidgets** is installed and configured for your toolset
3. Build and run

## Examples

Example input programs are in `testAsm/` (Counting to 10, Fibonacci, etc.).

## Known limitations / notes

- The Hack instruction set is intentionally small. Some computations do not exist.
  For example, `testAsm/Parity of number.asm` contains `D=D%A` with a comment that this computation does not exist for Hack — it was kept as a reminder/test case.
- The current GUI writes temporary files in the working directory (e.g. `temp.asm`, `output.hack`).

## License

MIT — see `LICENSE`.