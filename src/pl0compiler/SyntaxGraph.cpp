/**
 * \author Max Sperling
 */

#include "SyntaxGraph.hpp"

namespace pl0compiler {

using Graph = SyntaxGraph;
using Trans = Graph::Trans;
using TType = common::Token::Type;
using IRCCr = IRCodeCreator;

Trans::Trans(const Type type, const void* const value, const unsigned int idxNext, const unsigned int idxAlter, const func funct)
    : m_type(type), m_value(value), m_idxNext(idxNext), m_idxAlter(idxAlter), m_funct(funct) {}

const Trans* Graph::getEntrance()
{
    return &s_program.at(0);
}

const std::array<Trans, 4> SyntaxGraph::s_program =
{
/* 0*/ Trans(Trans::Nil,        nullptr,         1, 0, &IRCCr::codeStart),    /*(A)----------->(B)*/
/* 1*/ Trans(Trans::GraphStart, &Graph::s_block, 2, 0, nullptr),              /*(B)---BLOCK--->(C)*/
/* 2*/ Trans(Trans::Symbol,     ".",             3, 0, &IRCCr::procedureEnd), /*(C)----'.'---->(D)*/
/* 3*/ Trans(Trans::GraphEnd,   nullptr,         0, 0, &IRCCr::codeEnd)       /*(D)----------(END)*/
};

const std::array<Trans, 21> SyntaxGraph::s_block =
{
/* 0*/ Trans(Trans::Symbol,     "CONST",                       2,  1, nullptr),                /*(A)--->CONST--->(B)*/
/* 1*/ Trans(Trans::Nil,        nullptr,                       7,  0, nullptr),                /* +------------->(F)*/
/* 2*/ Trans(Trans::Token,      new TType(TType::Identifier),  3,  0, &IRCCr::addSymbol),      /*(B)----ident--->(C)*/
/* 3*/ Trans(Trans::Symbol,     "=",                           4,  0, nullptr),                /*(C)-----'='-----(D)*/
/* 4*/ Trans(Trans::Token,      new TType(TType::Number),      5,  0, &IRCCr::addConstant),    /*(D)--->number-->(E)*/
/* 5*/ Trans(Trans::Symbol,     ",",                           2,  6, nullptr),                /*(E)-----','-----(B)*/
/* 6*/ Trans(Trans::Symbol,     ";",                           7,  0, nullptr),                /* +------';'-----(F)*/
/* 7*/ Trans(Trans::Symbol,     "VAR",                         9,  8, nullptr),                /*(F)--->VAR----->(G)*/
/* 8*/ Trans(Trans::Nil,        nullptr,                      12,  0, nullptr),                /* +------------->(J)*/
/* 9*/ Trans(Trans::Token,      new TType(TType::Identifier), 10,  0, &IRCCr::addSymbol),      /*(G)----ident--->(H)*/
/*10*/ Trans(Trans::Symbol,     ",",                           9, 11, &IRCCr::addVariable),    /*(H)-----','-----(G)*/
/*11*/ Trans(Trans::Symbol,     ";",                          12,  0, &IRCCr::addVariable),    /*(H)-----';'-----(I)*/
/*12*/ Trans(Trans::Symbol,     "PROCEDURE",                  14, 13, nullptr),                /*(I)->PROCEDURE->(J)*/
/*13*/ Trans(Trans::Nil,        nullptr,                      19,  0, &IRCCr::procedureStart), /* +--------------(O)*/
/*14*/ Trans(Trans::Token,      new TType(TType::Identifier), 15,  0, &IRCCr::addSymbol),      /*(J)----ident--->(K)*/
/*15*/ Trans(Trans::Symbol,     ";",                          16,  0, &IRCCr::addProcedure),   /*(K)-----';'-----(L)*/
/*16*/ Trans(Trans::GraphStart, &Graph::s_block,              17,  0, nullptr),                /*(L)----block----(M)*/
/*17*/ Trans(Trans::Symbol,     ";",                          18,  0, &IRCCr::procedureEnd),   /*(M)-----';'-----(N)*/
/*18*/ Trans(Trans::Nil,        nullptr,                      12,  0, &IRCCr::retProcedure),   /*(N)------------>(I)*/
/*19*/ Trans(Trans::GraphStart, &Graph::s_statement,          20,  0, nullptr),                /*(O)--statement->(P)*/
/*20*/ Trans(Trans::GraphEnd,   nullptr,                       0,  0, nullptr)                 /*(P)-----------(END)*/
};

const std::array<Trans, 26> Graph::s_statement =
{
/* 0*/ Trans(Trans::Token,      new TType(TType::Identifier),  1,  3, &IRCCr::beforeAssignment), /*(A)----ident--->(B)*/
/* 1*/ Trans(Trans::Symbol,     ":=",                          2,  0, nullptr),                  /*(B)-----':='----(C)*/
/* 2*/ Trans(Trans::GraphStart, &Graph::s_expression,         25,  0, &IRCCr::afterAssignment),  /*(C)-expression->(Q)*/
/* 3*/ Trans(Trans::Symbol,     "IF",                          4,  7, nullptr),                  /* +------IF------(D)*/
/* 4*/ Trans(Trans::GraphStart, &Graph::s_condition,           5,  0, &IRCCr::condition),        /*(D)--condition->(E)*/
/* 5*/ Trans(Trans::Symbol,     "THEN",                        6,  0, nullptr),                  /*(E)--->THEN---->(F)*/
/* 6*/ Trans(Trans::GraphStart, &Graph::s_statement,          25,  0, &IRCCr::branchEnd),        /*(F)--statement->(Q)*/
/* 7*/ Trans(Trans::Symbol,     "WHILE",                       8, 11, &IRCCr::loopStart),        /* +-----WHILE----(G)*/
/* 8*/ Trans(Trans::GraphStart, &Graph::s_condition,           9,  0, &IRCCr::condition),        /*(G)--condition->(H)*/
/* 9*/ Trans(Trans::Symbol,     "DO",                         10,  0, nullptr),                  /*(H)---->DO----->(I)*/
/*10*/ Trans(Trans::GraphStart, &Graph::s_statement,          25,  0, &IRCCr::loopEnd),          /*(I)--statement->(Q)*/
/*11*/ Trans(Trans::Symbol,     "BEGIN",                      12, 15, nullptr),                  /* +-----BEGIN----(J)*/
/*12*/ Trans(Trans::GraphStart, &Graph::s_statement,          13,  0, nullptr),                  /*(J)--statement->(K)*/
/*13*/ Trans(Trans::Symbol,     ";",                          12, 14, nullptr),                  /*(K)-----';'---->(J)*/
/*14*/ Trans(Trans::Symbol,     "END",                        25,  0, nullptr),                  /*(K)-----END---->(Q)*/
/*15*/ Trans(Trans::Symbol,     "CALL",                       16, 17, nullptr),                  /* +-----CALL-----(L)*/
/*16*/ Trans(Trans::Token,      new TType(TType::Identifier), 25,  0, &IRCCr::callProcedure),    /*(L)----ident--->(Q)*/
/*17*/ Trans(Trans::Symbol,     "?",                          18, 19, nullptr),                  /* +------'?'-----(M)*/
/*18*/ Trans(Trans::Token,      new TType(TType::Identifier), 25,  0, &IRCCr::inputNumber),      /*(M)----ident--->(Q)*/
/*19*/ Trans(Trans::Symbol,     "!",                          20, 24, nullptr),                  /* +------'!'-----(N)*/
/*20*/ Trans(Trans::Symbol,     "\"",                         21, 23, nullptr),                  /*(N)-----'"'---->(O)*/
/*21*/ Trans(Trans::Token,      new TType(TType::String),     22,  0, &IRCCr::outputString),     /*(O)---string--->(P)*/
/*22*/ Trans(Trans::Symbol,     "\"",                         25,  0, nullptr),                  /*(P)-----'"'---->(Q)*/
/*23*/ Trans(Trans::GraphStart, &Graph::s_expression,         25,  0, &IRCCr::outputNumber),     /* +--expression->(Q)*/
/*24*/ Trans(Trans::Nil,        nullptr,                      25,  0, nullptr),                  /* +--------------(Q)*/
/*25*/ Trans(Trans::GraphEnd,   nullptr,                       0,  0, nullptr)                   /*(Q)-----------(END)*/
};

const std::array<Trans, 11> Graph::s_condition =
{
/* 0*/ Trans(Trans::Symbol,     "ODD",                 1, 2, nullptr),                /*(A)----ODD----->(D)*/
/* 1*/ Trans(Trans::GraphStart, &Graph::s_expression, 10, 0, &IRCCr::notEqual),       /*(B)---express-->(E)*/
/* 2*/ Trans(Trans::GraphStart, &Graph::s_expression,  3, 0, nullptr),                /* +----express-->(C)*/
/* 3*/ Trans(Trans::Symbol,     "=",                   9, 4, &IRCCr::equal),          /*(C)----'='----->(D)*/
/* 4*/ Trans(Trans::Symbol,     "#",                   9, 5, &IRCCr::notEqual),       /* +-----'#'----->(D)*/
/* 5*/ Trans(Trans::Symbol,     "<",                   9, 6, &IRCCr::smaller),        /* +-----'<'----->(D)*/
/* 6*/ Trans(Trans::Symbol,     "<=",                  9, 7, &IRCCr::lessOrEqual),    /* +-----'<='---->(D)*/
/* 7*/ Trans(Trans::Symbol,     ">",                   9, 8, &IRCCr::larger),         /* +-----'>'----->(D)*/
/* 8*/ Trans(Trans::Symbol,     ">=",                  9, 0, &IRCCr::greaterOrEqual), /* +-----'>='---->(D)*/
/* 9*/ Trans(Trans::GraphStart, &Graph::s_expression, 10, 0, &IRCCr::comparison),     /*(D)---express-->(E)*/
/*10*/ Trans(Trans::GraphEnd,   nullptr,               0, 0, nullptr)                 /*(E)-----------(END)*/
};

const std::array<Trans, 8> Graph::s_expression =
{
/* 0*/ Trans(Trans::Symbol,     "-",            2,  1, &IRCCr::negation),    /*(A)----'-'----->(B)*/
/* 1*/ Trans(Trans::Nil,        nullptr,        2,  0, nullptr),             /* +------------->(B)*/
/* 2*/ Trans(Trans::GraphStart, &Graph::s_term, 3,  0, nullptr),             /*(B)----term---->(C)*/
/* 3*/ Trans(Trans::Symbol,     "+",            4,  5, nullptr),             /*(C)-----'+'---->(D)*/
/* 4*/ Trans(Trans::GraphStart, &Graph::s_term, 3,  0, &IRCCr::addition),    /*(D)----term---->(C)*/
/* 5*/ Trans(Trans::Symbol,     "-",            6,  7, nullptr),             /* +------'-'---->(E)*/
/* 6*/ Trans(Trans::GraphStart, &Graph::s_term, 3,  0, &IRCCr::subtraction), /*(E)----term---->(C)*/
/* 7*/ Trans(Trans::GraphEnd,   nullptr,        0,  0, nullptr)              /* +------------(END)*/
};

const std::array<Trans, 7> Graph::s_term =
{
/* 0*/ Trans(Trans::GraphStart, &Graph::s_factor, 1, 0, nullptr),                /*(A)---faktor--->(B)*/
/* 1*/ Trans(Trans::Nil,        nullptr,          2, 0, nullptr),                /*(B)------------>(C)*/
/* 2*/ Trans(Trans::Symbol,     "*",              3, 4, nullptr),                /*(C)----'*'----->(D)*/
/* 3*/ Trans(Trans::GraphStart, &Graph::s_factor, 1, 0, &IRCCr::multiplication), /*(D)---faktor--->(B)*/
/* 4*/ Trans(Trans::Symbol,     "/",              5, 6, nullptr),                /* +-----'/'----->(E)*/
/* 5*/ Trans(Trans::GraphStart, &Graph::s_factor, 1, 0, &IRCCr::division),       /*(E)---faktor--->(B)*/
/* 6*/ Trans(Trans::GraphEnd,   nullptr,          0, 0, nullptr)                 /* +------------(END)*/
};

const std::array<Trans, 6> Graph::s_factor =
{
/* 0*/ Trans(Trans::Token,      new TType(TType::Number),     5, 1, &IRCCr::constByVal),  /*(A)---number--->(D)*/
/* 1*/ Trans(Trans::Symbol,     "(",                          2, 4, nullptr),             /* +-----'('----->(B)*/
/* 2*/ Trans(Trans::GraphStart, &Graph::s_expression,         3, 0, nullptr),             /*(B)---express-->(C)*/
/* 3*/ Trans(Trans::Symbol,     ")",                          5, 0, nullptr),             /*(C)----')'----->(D)*/
/* 4*/ Trans(Trans::Token,      new TType(TType::Identifier), 5, 0, &IRCCr::identByName), /* +----ident---->(D)*/
/* 5*/ Trans(Trans::GraphEnd,   nullptr,                      0, 0, nullptr)              /*(D)-----------(END)*/
};

}
