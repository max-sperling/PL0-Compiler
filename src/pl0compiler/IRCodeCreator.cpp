/**
 * \author Max Sperling
 */

#include "IRCodeCreator.hpp"

#include "common/Exception.hpp"

namespace pl0compiler {

void IRCodeCreator::AddSymbol(void* tok)
{
    m_symbols.addSymbol(static_cast<const common::Token* const>(tok)->getVal());
}

void IRCodeCreator::AddProcedure(void* tok)
{
    m_symbols.addProcedure();
}

void IRCodeCreator::RetProcedure(void* tok)
{
    m_symbols.retProcedure();
}

void IRCodeCreator::AddVariable(void* tok)
{
    m_symbols.addVariable();
}

void IRCodeCreator::AddConstant(void* tok)
{
    m_symbols.addConstant(stol(static_cast<const common::Token* const>(tok)->getVal()));
}

void IRCodeCreator::CodeStart(void* tok)
{
    writeInt(0);
}

void IRCodeCreator::ProcedureStart(void* tok)
{
    m_procStartAddr.push(m_binary.size() + sizeof(char));
    std::vector<short> param;
    param.push_back(0);
    param.push_back(m_symbols.getCurProcIdx());
    param.push_back(m_symbols.getCurProcNumVar() * sizeof(int));
    writeCode(Opcode::EntryProc, param);
}

void IRCodeCreator::ProcedureEnd(void* tok)
{
    writeCode(Opcode::RetProc);
    short distProc = m_binary.size() + sizeof(char) - m_procStartAddr.top();
    writeShortToAddr(m_procStartAddr.top(), distProc);
    m_procStartAddr.pop();
}

void IRCodeCreator::BeforeAssignment(void* tok)
{
    if (!pushVarByName(static_cast<const common::Token* const>(tok), Addr))
    {
        throw common::Exception(static_cast<const common::Token* const>(tok));
    }
}

void IRCodeCreator::AfterAssignment(void* tok)
{
    writeCode(Opcode::StoreVal);
}

void IRCodeCreator::InputNumber(void* tok)
{
    if (!pushVarByName(static_cast<const common::Token* const>(tok), Addr))
    {
        throw common::Exception(static_cast<const common::Token* const>(tok));
    }
    writeCode(Opcode::GetVal);
}

void IRCodeCreator::OutputNumber(void* tok)
{
    writeCode(Opcode::PutVal);
}

void IRCodeCreator::Negation(void* tok)
{
    writeCode(Opcode::VzMinus);
}

void IRCodeCreator::Addition(void* tok)
{
    writeCode(Opcode::OpAdd);
}

void IRCodeCreator::Subtraction(void* tok)
{
    writeCode(Opcode::OpSub);
}

void IRCodeCreator::Multiplication(void* tok)
{
    writeCode(Opcode::OpMult);
}

void IRCodeCreator::Division(void* tok)
{
    writeCode(Opcode::OpDiv);
}

void IRCodeCreator::ConstByVal(void* tok)
{
    pushConstByVal((common::Token*)tok);
}

void IRCodeCreator::IdentByName(void* tok)
{
    if (pushVarByName(static_cast<const common::Token* const>(tok), Val)) { return; }
    if (pushConstByName(static_cast<const common::Token* const>(tok))) { return; }
    throw common::Exception(static_cast<const common::Token* const>(tok));
}

void IRCodeCreator::Odd(void* tok)
{
    writeCode(Opcode::OpOdd);
}

void IRCodeCreator::Equal(void* tok)
{
    m_cmpOp = Opcode::CmpEq;
}

void IRCodeCreator::NotEqual(void * tok)
{
    m_cmpOp = Opcode::CmpNe;
}

void IRCodeCreator::Smaller(void* tok)
{
    m_cmpOp = Opcode::CmpLt;
}

void IRCodeCreator::Larger(void* tok)
{
    m_cmpOp = Opcode::CmpGt;
}

void IRCodeCreator::LessOrEqual(void* tok)
{
    m_cmpOp = Opcode::CmpLe;
}

void IRCodeCreator::GreaterOrEqual(void* tok)
{
    m_cmpOp = Opcode::CmpGe;
}

void IRCodeCreator::Comparison(void* tok)
{
    writeCode(static_cast<const Opcode>(m_cmpOp));
}

void IRCodeCreator::Condition(void* tok)
{
    std::vector<short> param;
    param.push_back(0);
    writeCode(Opcode::Jnot, param);
    m_jumpStartAddr.push(m_binary.size());
}

void IRCodeCreator::BranchEnd(void* tok)
{
    short jmpAddr = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    short distFromCond = m_binary.size() - jmpAddr;
    writeShortToAddr(jmpAddr - sizeof(short), distFromCond);
}

void IRCodeCreator::While(void* tok)
{
    m_jumpStartAddr.push(m_binary.size());
}

void IRCodeCreator::LoopEnd(void* tok)
{
    short jmpAddrIf = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();
    short jmpAddrWhile = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    std::vector<short> param;
    param.push_back(0);
    writeCode(Opcode::Jmp, param);
    short distToWhile = -(m_binary.size() - jmpAddrWhile);
    writeShortToAddr(m_binary.size() - sizeof(short), distToWhile);

    short distFromCond = m_binary.size() - jmpAddrIf;
    writeShortToAddr(jmpAddrIf - sizeof(short), distFromCond);
}

void IRCodeCreator::CallProcedure(void* tok)
{
    if (!pushProcByName(static_cast<const common::Token* const>(tok)))
    {
        throw common::Exception(static_cast<const common::Token* const>(tok));
    }
}

void IRCodeCreator::OutputString(void* tok)
{
    writeCode(Opcode::PutStrg);
    writeString(static_cast<const common::Token* const>(tok)->getVal());
}

void IRCodeCreator::CodeEnd(void* tok)
{
    for (auto& cons : m_symbols.m_vecConst)
    {
        writeInt(cons);
    }
    writeIntToAddr(0, m_symbols.m_numProc);
}


std::deque<char> IRCodeCreator::getBinary()
{
    return m_binary;
}

void IRCodeCreator::writeCode(Opcode code, std::vector<short> param)
{
    m_binary.push_back(code);

    for (short par : param)
    {
        m_binary.push_back(par & 0xff);
        m_binary.push_back((par >> 8) & 0xff);
    }
}

void IRCodeCreator::writeString(std::string value)
{
    for (auto& byte : value)
    {
        m_binary.push_back(byte);
    }
    m_binary.push_back(0);
}

void IRCodeCreator::writeInt(int value)
{
    m_binary.push_back(value & 0xff);
    m_binary.push_back((value >> 8) & 0xff);
    m_binary.push_back((value >> 16) & 0xff);
    m_binary.push_back((value >> 24) & 0xff);
}

void IRCodeCreator::writeShortToAddr(int startAddr, short value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
}

void IRCodeCreator::writeIntToAddr(int startAddr, int value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
    m_binary.at(startAddr+2) = ((value >> 16) & 0xff);
    m_binary.at(startAddr+3) = ((value >> 24) & 0xff);
}

bool IRCodeCreator::pushVarByName(const common::Token* const tok, AddrOrVal addrOrVal)
{
    Symbols::Symbol* symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) { return false; }
    if (symb->m_object->getType() != Symbols::Object::Var) { return false; }

    std::vector<short> param;
    param.push_back(symb->m_object->m_index * sizeof(int));

    if (symb->m_procIdx == m_symbols.getCurProcIdx())
    {
        switch (addrOrVal)
        {
        case Addr:
            writeCode(Opcode::PuAdrVrLocl, param);
            break;
        case Val:
            writeCode(Opcode::PuValVrLocl, param);
            break;
        }

    }
    else if (symb->m_procIdx == 0)
    {
        switch (addrOrVal)
        {
        case Addr:
            writeCode(Opcode::PuAdrVrMain, param);
            break;
        case Val:
            writeCode(Opcode::PuValVrMain, param);
            break;
        }
    }
    else
    {
        param.push_back(symb->m_procIdx);
        switch (addrOrVal)
        {
        case Addr:
            writeCode(Opcode::PuAdrVrGlob, param);
            break;
        case Val:
            writeCode(Opcode::PuValVrGlob, param);
            break;
        }
    }
    return true;
}

bool IRCodeCreator::pushConstByName(const common::Token* const tok)
{
    Symbols::Symbol* symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) { return false; }
    if (symb->m_object->getType() != Symbols::Object::Cons) { return false; }

    std::vector<short> param;
    param.push_back(static_cast<Symbols::Constant*>(symb->m_object)->m_value);
    writeCode(Opcode::PuConst, param);

    return true;
}

bool IRCodeCreator::pushConstByVal(const common::Token* const tok)
{
    std::vector<short> param;

    for (unsigned int i=0; i<m_symbols.m_vecConst.size(); i++)
    {
        if (m_symbols.m_vecConst.at(i) == stol(tok->getVal()))
        {
            param.push_back(i);
            writeCode(Opcode::PuConst, param);
            return true;
        }
    }

    param.push_back(m_symbols.m_vecConst.size());
    writeCode(Opcode::PuConst, param);
    m_symbols.addConstNum(stol(tok->getVal()));

    return true;
}

bool IRCodeCreator::pushProcByName(const common::Token* const tok)
{
    Symbols::Symbol* symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) { return false; }
    if (symb->m_object->getType() != Symbols::Object::Proc) { return false; }

    std::vector<short> param;
    param.push_back(symb->m_object->m_index);
    writeCode(Opcode::Call, param);

    return true;
}

}
