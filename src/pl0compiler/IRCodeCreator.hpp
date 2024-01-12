#pragma once
/**
 * \author Max Sperling
 */

#include "Symbols.hpp"
#include "common/Token.hpp"

#include "opcode.h"

#include <string>
#include <stack>
#include <deque>

namespace pl0compiler {

class IRCodeCreator
{
public:
    void addSymbol(void* tok);
    void addProcedure(void* tok);
    void retProcedure(void* tok);
    void addVariable(void* tok);
    void addConstant(void* tok);

    void codeStart(void* tok);
    void procedureStart(void* tok);
    void procedureEnd(void* tok);
    void beforeAssignment(void* tok);
    void afterAssignment(void* tok);
    void inputNumber(void* tok);
    void outputNumber(void* tok);
    void negation(void* tok);
    void addition(void* tok);
    void subtraction(void* tok);
    void multiplication(void* tok);
    void division(void* tok);
    void constByVal(void* tok);
    void identByName(void* tok);
    void odd(void* tok);
    void equal(void* tok);
    void notEqual(void* tok);
    void smaller(void* tok);
    void larger(void* tok);
    void lessOrEqual(void* tok);
    void greaterOrEqual(void* tok);
    void comparison(void* tok);
    void condition(void* tok);
    void branchEnd(void* tok);
    void loopStart(void* tok);
    void loopEnd(void* tok);
    void callProcedure(void* tok);
    void outputString(void* tok);
    void codeEnd(void* tok);

    std::deque<char> getBinary();

private:
    enum AddrOrVal
    {
        Addr,
        Val
    };

    void writeCode(Opcode code, std::vector<short> param = std::vector<short>());
    void writeString(std::string value);
    void writeInt(int value);
    void writeShortToAddr(int startAddr, short value);
    void writeIntToAddr(int startAddr, int value);

    bool pushVarByName(const common::Token* const tok, AddrOrVal addrOrVal);
    bool pushConstByName(const common::Token* const tok);
    bool pushConstByVal(const common::Token* const tok);
    bool pushProcByName(const common::Token* const tok);

    std::deque<char> m_binary;
    Symbols m_symbols;

    std::stack<int> m_procStartAddr;
    std::stack<int> m_jumpStartAddr;
    char m_cmpOp;
};

}
