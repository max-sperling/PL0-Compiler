/**
 * \author Max Sperling
 */

#include "Token.hpp"

namespace pl0compiler { namespace common {

Token::Token() { reset(); }

void Token::reset(int row, int col)
{
    m_row  = row;
    m_col  = col;
    m_type = Type::Undefined;
    m_val  = "";
}

unsigned int Token::getRow() const
{
    return m_row;
}

unsigned int Token::getCol() const
{
    return m_col;
}

Token::Type Token::getType() const
{
    return m_type;
}

void Token::setType(Token::Type type)
{
    m_type = type;
}

std::string Token::getVal() const
{
    return m_val;
}

void Token::addVal(char c)
{
    m_val += c;
}

} }
