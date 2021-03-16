#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "common/Token.hpp"

#include <vector>
#include <string>
#include <deque>

namespace pl0compiler {

class Tokenizer
{
public:
    Tokenizer();
    void reset();

    /**
     * @param[in]  srcCode ... source code
     * @param[out] token   ... token list
     */
    void exec(std::string &srcCode, std::deque<common::Token> &token);

private:
    typedef void (Tokenizer::*func)();

    static const std::vector<int> s_classVec;
    static const std::vector<std::vector<int>> s_stateMat;
    static const std::vector<std::vector<func>> s_functMat;
    static const std::vector<std::string> s_keywords;

    void tok();
    void r();
    void wr();
    void gr();
    void wrc();
    void c();

    unsigned int m_srcPos;
    unsigned int m_srcRow;
    unsigned int m_srcCol;
    unsigned int m_fsmState;

    std::string *m_srcCode;
    std::deque<common::Token> *m_token;
    common::Token m_curToken;
};

}
