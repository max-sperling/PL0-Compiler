#pragma once
/**
 * \author Max Sperling
 */

#include "common/Logger.hpp"

#include <string>
#include <deque>

namespace pl0compiler {

class CompilerTest
{
public:
    CompilerTest(const common::Logger& logger);

    /**
     * @param[in]  srcCode         ... source code
     * @param[out] expectedBinCode ... expected binary code
     */
    void exec(std::string& srcCode, const std::string& expectedBinCode);

private:
    const common::Logger& m_logger;
};

}
