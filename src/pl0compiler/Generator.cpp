/************************/
/* Author: Max Sperling */
/************************/

#include "Generator.hpp"

#include "IRCreator.hpp"
#include "common/Exception.hpp"

namespace pl0compiler { namespace compiler {

void Generator::exec(std::deque<common::Token> & token, std::deque<char> & binary)
{
    m_token = &token;
    generate(Graph::getEntrance());
    binary = m_irCreator.getBinary();
}

void Generator::generate(Graph::Trans const * curSect)
{
    bool IsFinished = false;
    const Graph::Trans *curTrans = curSect;

    while (!IsFinished)
    {
        switch (curTrans->m_type)
        {
        case Graph::Trans::Nil:
            execFunc(curTrans);
            curTrans = &curSect[curTrans->m_idxNext];
            break;
        case Graph::Trans::Symbol:
            if (std::string((char*)curTrans->m_value) == m_token->front().getVal())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
                m_token->pop_front();
            }
            else
            {
                if (curTrans->m_idxAlter == 0) throw common::Exception(&m_token->front());
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case Graph::Trans::Token:
            if (common::Token::Type(*(int*)curTrans->m_value) == m_token->front().getType())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
                m_token->pop_front();
            }
            else
            {
                if (curTrans->m_idxAlter == 0) throw common::Exception(&m_token->front());
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case Graph::Trans::GraphStart:
            try
            {
                generate((Graph::Trans*)curTrans->m_value);
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
            }
            catch (...)
            {
                if (curTrans->m_idxAlter == 0) throw common::Exception(&m_token->front());
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case Graph::Trans::GraphEnd:
            execFunc(curTrans);
            IsFinished = true;
            break;
        }
    }
}

void Generator::execFunc(Graph::Trans const * curTrans)
{
    if (curTrans->m_funct == nullptr) return;
    (m_irCreator.*curTrans->m_funct)((void*)&(m_token->front()));
}

} }
