# ⚙️ SystemC ALU Modules

This repository contains **SystemC** modules implementing basic arithmetic operations used in ALUs:

- ➕ 32-bit Ripple-Carry Adder (`rca32.h`)
- ➖ 32-bit Subtractor (`Subtractor32.h`)
- ✖️ Booth Multiplier (`booth_multiplier.h`)
- 🔁 Shift Unit – Left & Right (`shift_unit.h`)

## 📁 Project Structure

- main.cpp – testbench & simulation entry
- Header files for each arithmetic unit

## 🛠️ Build & Run

### Prerequisites
- [SystemC library](https://accellera.org/downloads/standards/systemc) installed and configured
- `CMake` and `MinGW` (or another compiler) available in PATH

### Steps

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
./main.exe
```

> 🚧 This project is under active development. New pages and future projects will be added soon!

### 👥 Contributors

- [@IoanaAdrian](https://github.com/IoanaAdrian)
- [@Dragos-AndreiIsfan](https://github.com/Dragos-AndreiIsfan)
- [@FlaviusMarian27](https://github.com/FlaviusMarian27)
- [@Mate44x05](https://github.com/Mate44x05)