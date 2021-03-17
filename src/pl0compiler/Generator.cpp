/**
 * \author Max Sperling
 */

#include "Generator.hpp"

#include "IRCodeCreator.hpp"
#include "common/Exception.hpp"

namespace pl0compiler {

void Generator::exec(std::deque<common::Token>& token, std::deque<char>& binary)
{
    m_token = &token;
    generate(SyntaxGraph::getEntrance());
    binary = m_irCodeCreator.getBinary();
}

void Generator::generate(const SyntaxGraph::Trans* const curSect)
{
    bool IsFinished = false;
    const SyntaxGraph::Trans *curTrans = curSect;

    while (!IsFinished)
    {
        switch (curTrans->m_type)
        {
        case SyntaxGraph::Trans::Nil:
            execFunc(curTrans);
            curTrans = &curSect[curTrans->m_idxNext];
            break;
        case SyntaxGraph::Trans::Symbol:
            if (std::string(static_cast<const char* const>(curTrans->m_value)) == m_token->front().getVal())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
                m_token->pop_front();
            }
            else
            {
                if (curTrans->m_idxAlter == 0) { throw common::Exception(&m_token->front()); }
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case SyntaxGraph::Trans::Token:
            if (common::Token::Type(*static_cast<const int* const>(curTrans->m_value)) == m_token->front().getType())
            {
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
                m_token->pop_front();
            }
            else
            {
                if (curTrans->m_idxAlter == 0) { throw common::Exception(&m_token->front()); }
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case SyntaxGraph::Trans::GraphStart:
            try
            {
                generate(static_cast<const SyntaxGraph::Trans* const>(curTrans->m_value));
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
            }
            catch (...)
            {
                if (curTrans->m_idxAlter == 0) { throw common::Exception(&m_token->front()); }
                curTrans = &curSect[curTrans->m_idxAlter];
            }
            break;
        case SyntaxGraph::Trans::GraphEnd:
            execFunc(curTrans);
            IsFinished = true;
            break;
        }
    }
}

void Generator::execFunc(const SyntaxGraph::Trans* const curTrans)
{
    if (curTrans->m_funct == nullptr) { return; }
    (m_irCodeCreator.*curTrans->m_funct)(static_cast<void* const>(&m_token->front()));
}

}
