#pragma once
/**
 * \author Max Sperling
 */

#include <string>
#include <vector>

namespace pl0compiler {

class Symbols
{
public:
    Symbols();
    ~Symbols();

    struct Object
    {
        enum Type
        {
            Proc, Var, Cons
        };

        virtual ~Object(){};
        virtual Type getType() = 0;

        int m_index;
    };

    struct Symbol
    {
        Symbol(std::string name, int procIdx);

        std::string m_name;
        int m_procIdx;
        Object* m_object;
    };

    struct Procedure : Object
    {
        Procedure(Procedure* parent, int index);
        Type getType();

        Procedure* m_parent;
        std::vector<Symbol> m_symbolTab;
        int m_numVar;
    };

    struct Variable : Object
    {
        Variable(int index);
        Type getType();
    };

    struct Constant : Object
    {
        Constant(long value, int index);
        Type getType();

        long m_value;
    };

    void addSymbol(std::string name);
    void addProcedure();
    void retProcedure();
    void delProcedure(Procedure* proc);
    void addVariable();
    void addConstant(long value);
    void addConstNum(long value);
    int getCurProcIdx();
    int getCurProcNumVar();
    Symbol* searchSymb(std::string name);

    unsigned int m_numProc;
    Procedure* m_curProc;
    std::vector<long> m_vecConst;
};

}
