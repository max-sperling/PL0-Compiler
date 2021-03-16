/************************/
/* Author: Max Sperling */
/************************/

#include "CompEx.hpp"

namespace pl0compiler { namespace compiler {

CompEx::CompEx(Token const * const token) : m_token(token) {}

std::string const CompEx::getError() const
{
    std::string const strErr = "Error: Value -> " + m_token->getVal()
                             + ", Row -> " + std::to_string(m_token->getRow())
                             + ", Col -> " + std::to_string(m_token->getCol())
                             + "\n";
    return strErr;
}

} }
