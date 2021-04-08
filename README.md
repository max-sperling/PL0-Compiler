# PL0-Compiler

## Description
The PL0-Compiler creates a CL0 bytecode based on the provided PL0 sourcecode. The CL0-Interpreter can then be used to interpret the created CL0 bytecode. <br>

## Workflow details
Sourcecode (PL0-Code) --[Tokenizer]--> Tokenlist --[Generator]--> Bytecode (CL0-Code) <br>

## Requirements
C++11 <br>
CMake <br>

## Build script generation
**PL0-Compiler:** cmake -H. -Bbuild/PL0-Compiler <br>
**CL0-Interpreter:** cmake -Hext/CL0-Interpreter -Bbuild/CL0-Interpreter <br>

## Execution
**PL0-Compiler:** \<App\> \<PL0-File\>.pl0 \<CL0-File\>.cl0 <br>
**CL0-Interpreter:** \<App\> \<CL0-File\>[.cl0] <br>
