/**
 * \author Max Sperling
 */

#include "Exception.hpp"

namespace pl0compiler { namespace common {

Exception::Exception(const Token* const token) : m_token(token) {}

const std::string Exception::getError() const
{
    const std::string strErr = "Error: Value -> " + m_token->getVal()
                             + ", Row -> " + std::to_string(m_token->getRow())
                             + ", Col -> " + std::to_string(m_token->getCol())
                             + "\n";
    return strErr;
}

} }
