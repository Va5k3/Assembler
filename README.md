# Hack Assembler (nand2tetris) — C++ / wxWidgets

A small assembler for the **Hack computer** from the *nand2tetris* course.

It translates Hack assembly (`.asm`) into Hack machine code (`.hack`). The project also includes a simple **wxWidgets GUI** for loading/pasting code, assembling it, previewing the output, and saving the result.

> **About this repo:** This started as a student project while learning nand2tetris.

---

## What it can do

- Assemble Hack assembly (`.asm`) → machine code (`.hack`)
- Classic **two-pass assembler**
  - **Pass 1:** collect labels `(LOOP)` and resolve ROM addresses
  - **Pass 2:** translate A/C instructions and allocate variables
- Symbol table
  - Predefined symbols: `SP`, `LCL`, `ARG`, `THIS`, `THAT`, `R0`..`R15`, `SCREEN`, `KBD`
  - User labels: `(LABEL)`
  - User variables: allocated starting at `RAM[16]`
- GUI
  - open `.asm` file or paste code
  - assemble
  - preview `.hack` output
  - save output
  - shows a simple symbol-table dump (`SymbolTable.txt`)

---

## How it works (quick overview)

Main pipeline is implemented in `Assembler.cpp`:

1. **Cleanup** (`Assembler::asmEdit`)
   - removes comments (`// ...`)
   - removes spaces
   - stores non-empty lines in a queue
2. **First pass** (`Assembler::firstPass`)
   - detects labels like `(LOOP)`
   - stores `label -> ROM address`
   - produces a second queue without label lines
3. **Second pass** (`Assembler::secondPass`)
   - translates each instruction via `Parser::parseInst`
   - writes 16-bit machine code to the output file

### A-instructions

- `@123` → `0` + 15-bit value
- `@symbol` → resolved with the symbol table
  - new variables are allocated starting at address 16

### C-instructions

Encoded as:

- `111` + `comp` (7 bits) + `dest` (3 bits) + `jump` (3 bits)

The lookup tables for `comp`, `dest`, `jump` are implemented in `Parser.cpp`.

---

## Project structure

- `Assembler.*` — two-pass assembler pipeline + symbol dump (`SymbolTable.txt`)
- `Parser.*` — parsing A/C instructions + comp/dest/jump dictionaries
- `SymbolTable.*` — predefined symbols + label/variable allocation
- `MainFrame.*`, `App.*` — wxWidgets GUI
- `testAsm/` — small example programs for manual testing

---

## Building / running (Windows)

This repository contains a Visual Studio project:

- `V45k3 - Assembler.vcxproj`

General steps:

1. Open the `.vcxproj` in Visual Studio
2. Install/configure **wxWidgets** for your toolset
3. Build and run

---

## Examples

Example input programs can be found in `testAsm/` (Counting to 10, Fibonacci, etc.).

---

## Notes / limitations

- Hack is intentionally small; some computations do not exist.
  - Example: `testAsm/Parity of number.asm` contains `D=D%A` as a reminder/test case.
- The GUI currently writes temporary files into the working directory (e.g. `temp.asm`, `output.hack`, `SymbolTable.txt`).

---

## License

MIT — see `LICENSE`.
