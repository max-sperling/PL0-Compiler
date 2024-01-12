/**
 * \author Max Sperling
 */

#include "CompilerTest.hpp"

#include "Compiler.hpp"
#include "common/Utils.hpp"

namespace pl0compiler {

CompilerTest::CompilerTest(const common::Logger& logger) : m_logger(logger) {}

void CompilerTest::exec(std::string& srcCode, const std::string& expectedBinCode)
{
    Compiler comp(m_logger);

    std::deque<char> actualBinCode;
    if (!comp.exec(srcCode, actualBinCode))
    {
        m_logger.error("Error while compiling");
    }

    if (common::toString(actualBinCode) == expectedBinCode)
    { m_logger.info("Test successful"); }
    else { m_logger.info("Test failed"); }
}

}
