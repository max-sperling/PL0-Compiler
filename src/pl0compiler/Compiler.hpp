#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "common/Logger.hpp"

#include <string>

namespace pl0compiler {

class Compiler
{
public:
    Compiler(common::Logger const &logger);

    /**
     * @param[in]  srcCode ... source code
     * @param[out] binCode ... binary code
     */
    bool exec(std::string &srcCode, std::deque<char> &binCode);

private:
    common::Logger const &m_logger;
};

}
