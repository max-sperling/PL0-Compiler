/**
 * \author Max Sperling
 */

#include "Tokenizer.hpp"

namespace pl0compiler {

using Tnz = Tokenizer;

Tokenizer::Tokenizer() { reset(); }

void Tokenizer::reset()
{
    m_srcPos   = 0;
    m_srcRow   = 0;
    m_srcCol   = 1;
    m_fsmState = 0;
}

void Tokenizer::exec(std::string& srcCode, std::deque<common::Token>& token)
{
    reset();

    m_srcCode = &srcCode;
    m_token = &token;
    m_curToken.reset(m_srcRow, m_srcCol);

    tokenize();
}

const std::array<int, 128> Tokenizer::s_classVec =
{
/*     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F     */
/*--------------------------------------------------------*/
/* 0*/ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/* 0*/
/*10*/ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/*10*/
/*20*/ 7, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/*20*/
/*30*/ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 5, 4, 6, 0,/*30*/
/*40*/ 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/*40*/
/*50*/ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 9, 0, 0, 0,/*50*/
/*60*/ 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/*60*/
/*70*/ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 /*70*/
};

const std::array<std::array<int, 10>, 12> Tokenizer::s_stateMat =
{{
/*      So  Zi  Bu  ':' '=' '<' '>' ' ' '"' '\'      */
/*---------------------------------------------------*/
/* 0*/ {{0,  1,  2,  3,  0,  4,  5,  0,  9,  0}},/* 0*/
/* 1*/ {{0,  1,  0,  0,  0,  0,  0,  0,  0,  0}},/* 1*/
/* 2*/ {{0,  2,  2,  0,  0,  0,  0,  0,  0,  0}},/* 2*/
/* 3*/ {{0,  0,  0,  0,  6,  0,  0,  0,  0,  0}},/* 3*/
/* 4*/ {{0,  0,  0,  0,  7,  0,  0,  0,  0,  0}},/* 4*/
/* 5*/ {{0,  0,  0,  0,  8,  0,  0,  0,  0,  0}},/* 5*/
/* 6*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}},/* 6*/
/* 7*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}},/* 7*/
/* 8*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}},/* 8*/
/* 9*/ {{9,  9,  9,  9,  9,  9,  9,  9, 11, 10}},/* 9*/
/*10*/ {{9,  9,  9,  9,  9,  9,  9,  9,  9,  9}},/*10*/
/*11*/ {{0,  0,  0,  0,  0,  0,  0,  0,  0,  0}} /*11*/
}};

const std::array<std::array<Tokenizer::func, 10>, 12> Tokenizer::s_functMat =
{{
/*          So         Zi         Bu         ':'       '='        '<'         '>'       ' '         ''         '\'          */
/*--------------------------------------------------------------------------------------------------------------------------*/
/* 0*/ {{&Tnz::wrc, &Tnz::wr,  &Tnz::gr,  &Tnz::wr,  &Tnz::wrc, &Tnz::wr,  &Tnz::wr,  &Tnz::r,   &Tnz::wrc, &Tnz::wrc}},/* 0*/
/* 1*/ {{&Tnz::c,   &Tnz::wr,  &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 1*/
/* 2*/ {{&Tnz::c,   &Tnz::wr,  &Tnz::gr,  &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 2*/
/* 3*/ {{&Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::wr,  &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 3*/
/* 4*/ {{&Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::wr,  &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 4*/
/* 5*/ {{&Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::wr,  &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 5*/
/* 6*/ {{&Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 6*/
/* 7*/ {{&Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 7*/
/* 8*/ {{&Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c,   &Tnz::c}},  /* 8*/
/* 9*/ {{&Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::c,   &Tnz::r}},  /* 9*/
/*10*/ {{&Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr,  &Tnz::wr}}, /*10*/
/*11*/ {{&Tnz::wrc, &Tnz::wrc, &Tnz::wrc, &Tnz::wrc, &Tnz::wrc, &Tnz::wrc, &Tnz::wrc, &Tnz::wrc, &Tnz::wrc, &Tnz::wrc}} /*11*/
}};

const std::array<std::string, 14> Tokenizer::s_keywords =
{
    "CALL","DO","WHILE","IF","THEN","ELSE","BEGIN","END",
    "ODD","PUT","GET","VAR","CONST","PROCEDURE"
};

void Tokenizer::tokenize()
{
    while (m_srcPos < m_srcCode->length())
    {
        int cTyp = s_classVec.at((int)m_srcCode->at(m_srcPos));
        (this->*s_functMat.at(m_fsmState).at(cTyp))();
        m_fsmState = s_stateMat.at(m_fsmState).at(cTyp);
    }
}

void Tokenizer::r()
{
    if (m_srcCode->at(m_srcPos) == '\n')
    {
        m_srcRow++;
        m_srcCol = 1;
    }
    else
    {
        m_srcCol++;
    }
    m_srcPos++;
}

void Tokenizer::wr()
{
    m_curToken.addVal(m_srcCode->at(m_srcPos));
    r();
}

void Tokenizer::gr()
{
    m_curToken.addVal(toupper(m_srcCode->at(m_srcPos)));
    r();
}

void Tokenizer::wrc()
{
    wr();
    c();
}

void Tokenizer::c()
{
    switch (m_fsmState)
    {
        // Number
        case 1:
            m_curToken.setType(common::Token::Type::Number);
            break;
        // Keyword or Identifier
        case 2:
            m_curToken.setType(common::Token::Type::Identifier);
            for (auto& keyword : s_keywords)
            {
                if (m_curToken.getVal() == keyword)
                {
                    m_curToken.setType(common::Token::Type::Keyword);
                    break;
                }
            }
            break;
        // std::string
        case 9:
            m_curToken.setType(common::Token::Type::String);
            break;
        // Symbol
        default:
            m_curToken.setType(common::Token::Type::Symbol);
            break;
    }

    m_token->push_back(m_curToken);
    m_curToken.reset(m_srcRow, m_srcCol);
}

}
