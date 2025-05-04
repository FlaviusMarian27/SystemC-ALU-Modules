# ⚙️ SystemC ALU Modules

# ⚙️ SystemC ALU Modules

A collection of reusable **SystemC** modules implementing fundamental ALU operations, combined into a parameterizable 8‐operation ALU:

- ➕ **RCA32**: 32‐bit ripple‐carry adder with carry‐in and carry‐out ports (`rca32.h`).
- ➖ **Subtractor32**: 32‐bit subtractor with borrow‐out (`Subtractor32.h`).
- ✖️ **BoothMultiplier**: Signed multiplier using Booth algorithm (template) producing 32‐bit result (`booth_multiplier.h`).
- 🔢 **ShiftUnit**: Parameterizable left/right shift unit (template) (`shift_unit.h`).
- 🔀 **Mux8_32**: 8‐to‐1 multiplexer of 32‐bit inputs (`Mux8_32.h`).
- 🔁 **SRT2Divider**: 16‐bit signed divider with quotient and remainder (`SRT2Divider.h`).
- 🔡 **Bitwise Logic**: AND, OR, XOR, NOT modules (32‐bit, unsigned templates) (`bitwise_and.h`, `bitwise_or.h`, `bitwise_xor.h`, `bitwise_not.h`).
- 🖥️ **ALU_mux**: Top‐level ALU module combining all above with a 3‐bit opcode and generating:
  - **ADD** (opcode 0) → sum + carry‐out
  - **SUB** (1) → difference + borrow
  - **MUL** (2) → low 32 bits of product
  - **DIV** (3) → quotient + remainder
  - **AND** (4), **OR** (5), **XOR** (6), **NOT** (7)

---

## 📁 Project Structure

```
├── CMakeLists.txt
├── README.md
├── main.cpp                # Testbench covering all 8 operations
├── rca32.h
├── Subtractor32.h
├── booth_multiplier.h
├── shift_unit.h
├── SRT2Divider.h
├── bitwise_and.h
├── bitwise_or.h
├── bitwise_xor.h
├── bitwise_not.h
├── Mux8_32.h
└── ALU_mux.h               # Top‐level ALU with opcode mux
```

---

## 🛠️ Build & Run

### Prerequisites

- **SystemC** (Accellera 2.3.3 or newer) installed and `SYSTEMC_HOME` set
- `CMake` 3.10+ and a C++11‐capable compiler (g++/MinGW, MSVC, clang)

### Steps

```bash
# Create build directory
mkdir build && cd build

# Generate build files
cmake -G "MinGW Makefiles" ..

# Compile
mingw32-make

# Run simulation
./main.exe
```

---

## 🚀 Usage

The provided `main.cpp` drives the `ALU` over a set of test vectors:

- **ADD** with different carry‐in values
- **SUBTRACT** with borrow detection
- **MULTIPLY** (signed Booth)
- **DIVIDE** (signed SRT2) printing quotient + remainder
- **BITWISE** logic operations

Sample output:

```
        SystemC 3.0.1-Accellera --- Mar 29 2025 20:05:04
        Copyright (c) 1996-2024 by all Contributors,
        ALL RIGHTS RESERVED

=== ADD ===
A=648 B=4 Cin=0 => S=652 Cout=0
A=5 B=6 Cin=1 => S=12 Cout=0

=== SUBTRACT ===
A=20 B=5 => S=15 Cout=1
A=45 B=15 => S=30 Cout=1

=== MULTIPLY (Booth) ===
A=7 * B=-3 => S=-21
A=-8 * B=-4 => S=32
A=7 * B=8 => S=56

=== DIVIDE ===
Dividend=1234 Divisor=56 => Quotient=22 Remainder=2
Dividend=-500 Divisor=13 => Quotient=-38 Remainder=-6

=== BITWISE AND ===
A=13 B=10 => S=8

=== BITWISE OR ===
A=13 B=10 => S=15

=== BITWISE XOR ===
A=13 B=10 => S=7

=== BITWISE NOT ===
A=13 => S=-14
```

---

> 🚧 This project is under active development. New functions and future projects will be added soon!

### 👥 Contributors

- [@IoanaAdrian](https://github.com/IoanaAdrian)
- [@Dragos-AndreiIsfan](https://github.com/Dragos-AndreiIsfan)
- [@FlaviusMarian27](https://github.com/FlaviusMarian27)
- [@Mate44x05](https://github.com/Mate44x05)