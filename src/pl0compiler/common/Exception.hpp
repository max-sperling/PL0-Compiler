#pragma once
/**
 * \author Max Sperling
 */

#include "Token.hpp"

#include <string>

namespace pl0compiler { namespace common {

class Exception : public std::exception
{
public:
    Exception(const Token* const token);
    const std::string getError() const;

private:
    const Token* const m_token;
};

} }
