# PL0-Compiler

## Requirements
C++11 <br>
CMake <br>

## Workflow
**PL0-Compiler:** Sourcecode (PL0-Code) --Tokenizer--> Tokenlist --Generator--> IR-Code (CL0-Code) <br>

## Building
**PL0-Compiler:** cmake -H. -Bbin/PL0-Comp <br>
**CL0-Interpreter:** cmake -Hext/CL0-Interpreter -Bbin/CL0-Interpreter <br>

## Executing
**PL0-Compiler:** \<App\> \<PL0-File\>.pl0 \<CL0-File\>.cl0 <br>
**CL0-Interpreter:** \<App\> \<CL0-File\> <br>
