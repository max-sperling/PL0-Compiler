#pragma once
/**
 * \author Max Sperling
 */

#include "common/Logger.hpp"

#include <string>

namespace pl0compiler {

class Compiler
{
public:
    Compiler(const common::Logger& logger);

    /**
     * @param[in]  srcCode ... source code
     * @param[out] binCode ... binary code
     */
    bool exec(std::string& srcCode, std::deque<char>& binCode);

private:
    const common::Logger& m_logger;
};

}
