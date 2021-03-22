#pragma once
/**
 * \author Max Sperling
 */

#include "pl0compiler/common/Logger.hpp"

#include <string>
#include <deque>

namespace pl0compilertest {

class CompilerTest
{
public:
    CompilerTest(const pl0compiler::common::Logger& logger);

    /**
     * @param[in]  srcCode         ... source code
     * @param[out] expectedBinCode ... expected binary code
     */
    void exec(std::string& srcCode, const std::string& expectedBinCode);

private:
    const pl0compiler::common::Logger& m_logger;
};

}
