/************************/
/* Author: Max Sperling */
/************************/

#include "Generator.hpp"

#include "IRCreator.hpp"
#include "common/Exception.hpp"

namespace pl0compiler {

void Generator::exec(std::deque<common::Token> &token, std::deque<char> &binary)
{
    m_token = &token;
    generate(Graph::getEntrance());
    binary = m_irCreator.getBinary();
}

void Generator::generate(Graph::Trans const *const curSect)
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
            if (std::string(static_cast<char const *const>(curTrans->m_value)) == m_token->front().getVal())
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
        case Graph::Trans::Token:
            if (common::Token::Type(*static_cast<int const *const>(curTrans->m_value)) == m_token->front().getType())
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
        case Graph::Trans::GraphStart:
            try
            {
                generate(static_cast<Graph::Trans const *const>(curTrans->m_value));
                execFunc(curTrans);
                curTrans = &curSect[curTrans->m_idxNext];
            }
            catch (...)
            {
                if (curTrans->m_idxAlter == 0) { throw common::Exception(&m_token->front()); }
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

void Generator::execFunc(Graph::Trans const *const curTrans)
{
    if (curTrans->m_funct == nullptr) { return; }
    (m_irCreator.*curTrans->m_funct)(static_cast<void *const>(&m_token->front()));
}

}
