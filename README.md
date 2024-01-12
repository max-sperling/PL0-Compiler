# PL0-Compiler

## Description
1. The "PL0-Compiler" creates a CL0 bytecode based on the provided PL0 sourcecode.
    1. Tokenizer: Sourcecode (PL0-Code) --> Tokenlist
    2. Generator: Tokenlist --> Bytecode (CL0-Code)
2. The "CL0-Interpreter" can then be used to interpret the created CL0 bytecode.

## Requirements
- CMake (Version >= 3.5)
- C++-Compiler (Standard >= C++11)

## Meta-Build
- "PL0-Compiler": cmake -H. -Bbuild/PL0-Compiler
- "CL0-Interpreter": cmake -Hext/CL0-Interpreter -Bbuild/CL0-Interpreter

## Execution
- "PL0-Compiler": \<App\> \<PL0-File\>.pl0 \<CL0-File\>.cl0
- "CL0-Interpreter": \<App\> \<CL0-File\>[.cl0]
