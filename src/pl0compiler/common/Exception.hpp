#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Token.hpp"

#include <string>

namespace pl0compiler { namespace common {

class Exception : public std::exception
{
public:
    Exception(Token const *const token);
    std::string const getError() const;

private:
    Token const *const m_token;
};

} }
