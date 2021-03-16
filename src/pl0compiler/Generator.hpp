#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "SyntaxGraph.hpp"
#include "common/Token.hpp"

#include <deque>

namespace pl0compiler {

class IRCreator;

class Generator
{
public:
    /**
     * @param[in]  token  ... token list
     * @param[out] binary ... binary list
     */
    void exec(std::deque<common::Token>& token, std::deque<char>& binary);

private:
    void generate(const SyntaxGraph::Trans* const curSect);
    void execFunc(const SyntaxGraph::Trans* const curTrans);

    IRCreator m_irCreator;
    std::deque<common::Token>* m_token;
};

}
