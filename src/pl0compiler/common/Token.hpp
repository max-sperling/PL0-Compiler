#pragma once
/**
 * \author Max Sperling
 */

#include <string>

namespace pl0compiler { namespace common {

class Token
{
public:
    Token();
    void reset(int row = 1, int col = 1);

    unsigned int getRow() const;
    unsigned int getCol() const;

    enum class Type
    {
        Undefined,
        Symbol,
        Number,
        Identifier,
        Keyword,
        String
    };

    Type getType() const;
    void setType(Type type);

    std::string getVal() const;
    void addVal(char c);

private:
    unsigned int m_row;
    unsigned int m_col;
    Type m_type;
    std::string m_val;
};

} }
