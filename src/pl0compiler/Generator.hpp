#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Graph.hpp"
#include "IRCreator.hpp"
#include "common/Token.hpp"

#include <deque>

namespace pl0compiler { namespace compiler {

class ILGen;

class Generator
{
public:
    /**
     * @param[in]  token  ... token list
     * @param[out] binary ... binary list
     */
    void exec(std::deque<common::Token> & token, std::deque<char> & binary);

private:
    void generate(Graph::Trans const * curSect);
    void execFunc(Graph::Trans const * curTrans);

    IRCreator m_irCreator;
    std::deque<common::Token> * m_token;
};

} }
