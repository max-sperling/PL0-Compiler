#pragma once
/**
 * \author Max Sperling
 */

#include "common/Token.hpp"

#include <array>
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
    void exec(std::string& srcCode, std::deque<common::Token>& token);

private:
    typedef void (Tokenizer::*func)();

    static const std::array<int, 128> s_classVec;
    static const std::array<std::array<int, 10>, 12> s_stateMat;
    static const std::array<std::array<func, 10>, 12> s_functMat;
    static const std::array<std::string, 14> s_keywords;

    void tokenize();

    /// read next char
    void r();

    /// write char to token then read next char
    void wr();

    /// write (upper case) char to token then read next char
    void gr();

    /// write char to token then read next char then save and clear token
    void wrc();

    /// save and clear token
    void c();

    unsigned int m_srcPos;
    unsigned int m_srcRow;
    unsigned int m_srcCol;
    unsigned int m_fsmState;

    std::string* m_srcCode;
    std::deque<common::Token>* m_token;
    common::Token m_curToken;
};

}
