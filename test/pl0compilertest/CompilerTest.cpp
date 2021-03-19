/**
 * \author Max Sperling
 */

#include "CompilerTest.hpp"

#include "common/Logger.hpp"
#include "common/Utils.hpp"
#include "Compiler.hpp"

namespace pl0compilertest {

void CompilerTest::runTest(const std::string& srcCode, const string& expectedBinCode)
{
    pl0compiler::common::Logger const logger(pl0compiler::common::Logger::Level::Info);
    pl0compiler::Compiler comp(logger);

    std::deque<char> actualBinCode;
    if (!comp.exec(srcCode, actualBinCode))
    {
        logger.error("Error while compiling");
    }

    if (common::toString(actualBinCode) == expectedBinCode) { logger.info("Test successful"); }
    else { logger.info("Test failed"); }
}

}
