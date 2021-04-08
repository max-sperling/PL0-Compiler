# PL0-Compiler

## Requirements
C++11 <br>
CMake <br>

## Workflow
**PL0-Compiler:** Sourcecode (PL0-Code) --[Tokenizer]--> Tokenlist --[Generator]--> Bytecode (CL0-Code) <br>

## Building
**PL0-Compiler:** cmake -H. -Bbuild/PL0-Compiler <br>
**CL0-Interpreter:** cmake -Hext/CL0-Interpreter -Bbuild/CL0-Interpreter <br>

## Executing
### Apps
**PL0-Compiler:** \<MainApp\> \<PL0-File\>.pl0 \<CL0-File\>.cl0 <br>
**CL0-Interpreter:** \<App\> \<CL0-File\>[.cl0] <br>
### Test
**PL0-Compiler:** \<TestApp\> <br>