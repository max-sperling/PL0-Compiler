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
    void AddSymbol(void* tok);
    void AddProcedure(void* tok);
    void RetProcedure(void* tok);
    void AddVariable(void* tok);
    void AddConstant(void* tok);

    void CodeStart(void* tok);
    void ProcedureStart(void* tok);
    void ProcedureEnd(void* tok);
    void BeforeAssignment(void* tok);
    void AfterAssignment(void* tok);
    void InputNumber(void* tok);
    void OutputNumber(void* tok);
    void Negation(void* tok);
    void Addition(void* tok);
    void Subtraction(void* tok);
    void Multiplication(void* tok);
    void Division(void* tok);
    void ConstByVal(void* tok);
    void IdentByName(void* tok);
    void Odd(void* tok);
    void Equal(void* tok);
    void NotEqual(void* tok);
    void Smaller(void* tok);
    void Larger(void* tok);
    void LessOrEqual(void* tok);
    void GreaterOrEqual(void* tok);
    void Comparison(void* tok);
    void Condition(void* tok);
    void BranchEnd(void* tok);
    void While(void* tok);
    void LoopEnd(void* tok);
    void CallProcedure(void* tok);
    void OutputString(void* tok);
    void CodeEnd(void* tok);

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
