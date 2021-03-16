/************************/
/* Author: Max Sperling */
/************************/

#include "IRCreator.hpp"

#include "common/Exception.hpp"

namespace pl0compiler { namespace compiler {

std::deque<char> IRCreator::getBinary()
{
    return m_binary;
}

void IRCreator::AddSymbol(void *tok)
{
    m_symbols.addSymbol(((common::Token*)tok)->getVal());
}

void IRCreator::AddProcedure(void *tok)
{
    m_symbols.addProcedure();
}

void IRCreator::RetProcedure(void *tok)
{
    m_symbols.retProcedure();
}

void IRCreator::AddVariable(void *tok)
{
    m_symbols.addVariable();
}

void IRCreator::AddConstant(void *tok)
{
    m_symbols.addConstant(stol(((common::Token*)tok)->getVal()));
}

void IRCreator::CodeStart(void *tok)
{
    writeInt(0);
}

void IRCreator::ProcedureStart(void *tok)
{
    m_procStartAddr.push(m_binary.size()+sizeof(char));
    std::vector<short> param;
    param.push_back(0);
    param.push_back(m_symbols.getCurProcIdx());
    param.push_back(m_symbols.getCurProcNumVar()*sizeof(int));
    writeCode(ByteCode::EntryProc, param);
}

void IRCreator::ProcedureEnd(void *tok)
{
    writeCode(ByteCode::RetProc);
    short distProc = m_binary.size()+sizeof(char)-m_procStartAddr.top();
    writeShortToAddr(m_procStartAddr.top(), distProc);
    m_procStartAddr.pop();
}

void IRCreator::BeforeAssignment(void *tok)
{
    if (!pushVarByName((common::Token*)tok, Addr))
    {
        throw common::Exception((common::Token*)tok);
    }
}

void IRCreator::AfterAssignment(void *tok)
{
    writeCode(ByteCode::StoreVal);
}

void IRCreator::InputNumber(void *tok)
{
    if (!pushVarByName((common::Token*)tok, Addr))
    {
        throw common::Exception((common::Token*)tok);
    }
    writeCode(ByteCode::GetVal);
}

void IRCreator::OutputNumber(void *tok)
{
    writeCode(ByteCode::PutVal);
}

void IRCreator::Negation(void *tok)
{
    writeCode(ByteCode::VzMinus);
}

void IRCreator::Addition(void *tok)
{
    writeCode(ByteCode::OpAdd);
}

void IRCreator::Subtraction(void *tok)
{
    writeCode(ByteCode::OpSub);
}

void IRCreator::Multiplication(void *tok)
{
    writeCode(ByteCode::OpMult);
}

void IRCreator::Division(void *tok)
{
    writeCode(ByteCode::OpDiv);
}

void IRCreator::ConstByVal(void *tok)
{
    pushConstByVal((common::Token*)tok);
}

void IRCreator::IdentByName(void *tok)
{
    if (pushVarByName((common::Token*)tok, Val)) return;
    if (pushConstByName((common::Token*)tok)) return;
    throw common::Exception((common::Token*)tok);
}

void IRCreator::Odd(void *tok)
{
    writeCode(ByteCode::OpOdd);
}

void IRCreator::Equal(void *tok)
{
    m_cmpOp = ByteCode::CmpEq;
}

void IRCreator::NotEqual(void *tok)
{
    m_cmpOp = ByteCode::CmpNe;
}

void IRCreator::Smaller(void *tok)
{
    m_cmpOp = ByteCode::CmpLt;
}

void IRCreator::Larger(void *tok)
{
    m_cmpOp = ByteCode::CmpGt;
}

void IRCreator::LessOrEqual(void *tok)
{
    m_cmpOp = ByteCode::CmpLe;
}

void IRCreator::GreaterOrEqual(void *tok)
{
    m_cmpOp = ByteCode::CmpGe;
}

void IRCreator::Comparison(void *tok)
{
    writeCode((ByteCode)m_cmpOp);
}

void IRCreator::Condition(void *tok)
{
    std::vector<short> param;
    param.push_back(0);
    writeCode(ByteCode::Jnot, param);
    m_jumpStartAddr.push(m_binary.size());
}

void IRCreator::BranchEnd(void *tok)
{
    short jmpAddr = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    short distFromCond = m_binary.size()-jmpAddr;
    writeShortToAddr(jmpAddr-sizeof(short), distFromCond);
}

void IRCreator::While(void *tok)
{
    m_jumpStartAddr.push(m_binary.size());
}

void IRCreator::LoopEnd(void *tok)
{
    short jmpAddrIf = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();
    short jmpAddrWhile = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    std::vector<short> param;
    param.push_back(0);
    writeCode(ByteCode::Jmp, param);
    short distToWhile = -(m_binary.size()-jmpAddrWhile);
    writeShortToAddr(m_binary.size()-sizeof(short), distToWhile);

    short distFromCond = m_binary.size()-jmpAddrIf;
    writeShortToAddr(jmpAddrIf-sizeof(short), distFromCond);
}

void IRCreator::CallProcedure(void *tok)
{
    if (!pushProcByName((common::Token*)tok))
    {
        throw common::Exception((common::Token*)tok);
    }
}

void IRCreator::OutputString(void *tok)
{
    writeCode(ByteCode::PutStrg);
    writeString(((common::Token*)tok)->getVal());
}

void IRCreator::CodeEnd(void *tok)
{
    for (auto &cons : m_symbols.m_vecConst)
    {
        writeInt(cons);
    }
    writeIntToAddr(0, m_symbols.m_numProc);
}

void IRCreator::writeCode(ByteCode code, std::vector<short> param)
{
    m_binary.push_back(code);

    for (short par : param)
    {
        m_binary.push_back(par & 0xff);
        m_binary.push_back((par >> 8) & 0xff);
    }
}

void IRCreator::writeString(std::string value)
{
    std::vector<char> vecVal(value.begin(), value.end());
    for (auto &val : vecVal)
    {
        m_binary.push_back(val);
    }
    m_binary.push_back(0);
}

void IRCreator::writeInt(int value)
{
    m_binary.push_back(value & 0xff);
    m_binary.push_back((value >> 8) & 0xff);
    m_binary.push_back((value >> 16) & 0xff);
    m_binary.push_back((value >> 24) & 0xff);
}

void IRCreator::writeShortToAddr(int startAddr, short value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
}

void IRCreator::writeIntToAddr(int startAddr, int value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
    m_binary.at(startAddr+2) = ((value >> 16) & 0xff);
    m_binary.at(startAddr+3) = ((value >> 24) & 0xff);
}

bool IRCreator::pushVarByName(common::Token *tok, AddrOrVal addrOrVal)
{
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) return false;
    if (symb->m_object->getType() != Symbols::Object::Var) return false;

    std::vector<short> param;
    param.push_back((symb->m_object->m_index)*sizeof(int));

    if (symb->m_procIdx == m_symbols.getCurProcIdx())
    {
        switch (addrOrVal)
        {
        case Addr:
            writeCode(ByteCode::PuAdrVrLocl, param);
            break;
        case Val:
            writeCode(ByteCode::PuValVrLocl, param);
            break;
        }

    }
    else if (symb->m_procIdx == 0)
    {
        switch (addrOrVal)
        {
        case Addr:
            writeCode(ByteCode::PuAdrVrMain, param);
            break;
        case Val:
            writeCode(ByteCode::PuValVrMain, param);
            break;
        }
    }
    else
    {
        param.push_back(symb->m_procIdx);
        switch (addrOrVal)
        {
        case Addr:
            writeCode(ByteCode::PuAdrVrGlob, param);
            break;
        case Val:
            writeCode(ByteCode::PuValVrGlob, param);
            break;
        }
    }
    return true;
}

bool IRCreator::pushConstByName(common::Token *tok)
{
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) return false;
    if (symb->m_object->getType() != Symbols::Object::Cons) return false;

    std::vector<short> param;
    param.push_back(((Symbols::Constant*)symb->m_object)->m_value);
    writeCode(ByteCode::PuConst, param);
    return true;
}

bool IRCreator::pushConstByVal(common::Token *tok)
{
    std::vector<short> param;

    for (unsigned int i=0; i<m_symbols.m_vecConst.size(); i++)
    {
        if (m_symbols.m_vecConst.at(i) == stol(tok->getVal()))
        {
            param.push_back(i);
            writeCode(ByteCode::PuConst, param);
            return true;
        }
    }

    param.push_back(m_symbols.m_vecConst.size());
    writeCode(ByteCode::PuConst, param);
    m_symbols.addConstNum(stol(tok->getVal()));
    return true;
}

 bool IRCreator::pushProcByName(common::Token *tok)
 {
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) return false;
    if (symb->m_object->getType() != Symbols::Object::Proc) return false;

    std::vector<short> param;
    param.push_back(symb->m_object->m_index);
    writeCode(ByteCode::Call, param);
    return true;
 }

} }
