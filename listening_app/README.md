# MyLanguageModelApp

A multi-language project combining C++ (Qt GUI), Python (cl4py bridge), and Lisp (compiled to .fasl).

## Structure

- **C++ (Qt GUI):** Provides the graphical user interface.
- **Python (cl4py bridge):** Acts as a bridge to call Lisp code.
- **Lisp:** Contains language model logic compiled to .fasl.

## Build Instructions

### C++ (Qt GUI)
Using CMake:
```bash
mkdir build
cd build
cmake ..
make
