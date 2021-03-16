#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "IRCreator.hpp"

#include <array>

namespace pl0compiler {

class Graph
{
public:
    typedef void (IRCreator::*func)(void *const);

    struct Trans
    {
        enum Type
        {
            Nil, Symbol, Token, GraphStart, GraphEnd
        };

        Trans(Type const type, void const *const value, unsigned int const idxNext,
              unsigned int const idxAlter, func const funct);

        Type const m_type;
        void const *const m_value;
        unsigned int const m_idxNext;
        unsigned int const m_idxAlter;
        func const m_funct;
    };

    static Trans *getEntrance();

private:
    static std::array<Trans,4> const s_program;
    static std::array<Trans,21> const s_block;
    static std::array<Trans,26> const s_statement;
    static std::array<Trans,11> const s_condition;
    static std::array<Trans,8> const s_expression;
    static std::array<Trans,7> const s_term;
    static std::array<Trans,6> const s_factor;
};

}
