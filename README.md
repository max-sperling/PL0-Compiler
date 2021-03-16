# PL0-Compiler

## Workflow
Sourcecode (PL0-Code) --Tokenizer--> Tokenlist --Generator--> IR-Code (CL0-Code) <br>

## Requirements
C++11 <br>
CMake <br>

## Building
**Compiler:** cmake -H. -Bbin/PL0-Comp <br>
**VM:** cmake -Hext/PL0-VM -Bbin/PL0-VM <br>

## Executing
**Compiler:** \<App\> \<PL0-File\>.pl0 \<CL0-File\>.cl0 <br>
**VM:** \<App\> \<CL0-File\> <br>
