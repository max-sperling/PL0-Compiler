/**
 * \author Max Sperling
 */

#include "CompilerTest.hpp"

#include "pl0compiler/Compiler.hpp"
#include "pl0compiler/common/Utils.hpp"

namespace pl0compiler {

CompilerTest::CompilerTest(const pl0compiler::common::Logger& logger) : m_logger(logger) {}

void CompilerTest::exec(std::string& srcCode, const std::string& expectedBinCode)
{
    pl0compiler::Compiler comp(m_logger);

    std::deque<char> actualBinCode;
    if (!comp.exec(srcCode, actualBinCode))
    {
        m_logger.error("Error while compiling");
    }

    if (pl0compiler::common::toString(actualBinCode) == expectedBinCode)
    { m_logger.info("Test successful"); }
    else { m_logger.info("Test failed"); }
}

}
