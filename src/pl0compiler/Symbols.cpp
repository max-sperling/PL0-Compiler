/**
 * \author Max Sperling
 */

#include "Symbols.hpp"

namespace pl0compiler {

Symbols::Symbols() : m_numProc(0), m_curProc(nullptr)
{
    addProcedure();
}

Symbols::~Symbols()
{
    while (m_curProc->m_parent != nullptr)
    {
        m_curProc = m_curProc->m_parent;
    }

    delProcedure(m_curProc);
    delete m_curProc;
}

Symbols::Symbol::Symbol(std::string name, int procIdx)
{
    m_name = name;
    m_procIdx = procIdx;
}

Symbols::Procedure::Procedure(Procedure* parent, int index)
{
    m_parent = parent;
    m_index = index;
    m_numVar = 0;
}

Symbols::Object::Type Symbols::Procedure::getType()
{
    return Proc;
}

Symbols::Variable::Variable(int index)
{
    m_index = index;
}

Symbols::Object::Type Symbols::Variable::getType()
{
    return Var;
}

Symbols::Constant::Constant(long value, int index)
{
    m_value = value;
    m_index = index;
}

Symbols::Object::Type Symbols::Constant::getType()
{
    return Cons;
}

void Symbols::addSymbol(std::string name)
{
    Symbol symb(name, m_curProc->m_index);
    m_curProc->m_symbolTab.push_back(symb);
}

void Symbols::addProcedure()
{
    Procedure* proc = new Procedure(m_curProc, m_numProc);
    if (m_curProc != nullptr)
    {
        m_curProc->m_symbolTab.back().m_object = proc;
    }
    m_curProc = proc;
    m_numProc++;
}

void Symbols::retProcedure()
{
    m_curProc = m_curProc->m_parent;
}

void Symbols::delProcedure(Procedure* proc)
{
    for (auto& symb : proc->m_symbolTab)
    {
        if (symb.m_object->getType() == Symbols::Object::Proc)
        {
            delProcedure(static_cast<Procedure*>(symb.m_object));
        }
        delete symb.m_object;
    }
}

void Symbols::addVariable()
{
    Variable* var = new Variable(m_curProc->m_numVar);
    m_curProc->m_symbolTab.back().m_object = var;
    m_curProc->m_numVar++;
}

void Symbols::addConstant(long value)
{
    Constant* cons = new Constant(value, m_vecConst.size());
    m_curProc->m_symbolTab.back().m_object = cons;
    m_vecConst.push_back(value);
}

void Symbols::addConstNum(long value)
{
    m_vecConst.push_back(value);
}

int Symbols::getCurProcIdx()
{
    return m_curProc->m_index;
}

int Symbols::getCurProcNumVar()
{
    return m_curProc->m_numVar;
}

Symbols::Symbol* Symbols::searchSymb(std::string name)
{
    Procedure* tmpProc = m_curProc;

    while (tmpProc != nullptr)
    {
        for (auto& symb : tmpProc->m_symbolTab)
        {
            if (symb.m_name == name) { return &symb; }
        }
        tmpProc = tmpProc->m_parent;
    }

    return nullptr;
}

}
