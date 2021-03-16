/************************/
/* Author: Max Sperling */
/************************/

#include "Exception.hpp"

namespace pl0compiler { namespace common {

Exception::Exception(Token const * const token) : m_token(token) {}

std::string const Exception::getError() const
{
    std::string const strErr = "Error: Value -> " + m_token->getVal()
                             + ", Row -> " + std::to_string(m_token->getRow())
                             + ", Col -> " + std::to_string(m_token->getCol())
                             + "\n";
    return strErr;
}

} }
