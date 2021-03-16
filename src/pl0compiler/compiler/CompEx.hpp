#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hpp"

#include <string>

namespace pl0compiler { namespace compiler {

class CompEx : public std::exception
{
public:
    CompEx(Token const * const token);
    std::string const getError() const;

private:
    Token const * const m_token;
};

} }
