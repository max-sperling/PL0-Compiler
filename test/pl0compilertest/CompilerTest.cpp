/**
 * \author Max Sperling
 */

#include "CompilerTest.hpp"

#include "pl0compiler/common/Logger.hpp"
#include "pl0compiler/common/Utils.hpp"
#include "pl0compiler/Compiler.hpp"

namespace pl0compilertest {

void CompilerTest::runTest(std::string& srcCode, const std::string& expectedBinCode)
{
    pl0compiler::common::Logger const logger(pl0compiler::common::Logger::Level::Info);
    pl0compiler::Compiler comp(logger);

    std::deque<char> actualBinCode;
    if (!comp.exec(srcCode, actualBinCode))
    {
        logger.error("Error while compiling");
    }

    if (pl0compiler::common::toString(actualBinCode) == expectedBinCode) { logger.info("Test successful"); }
    else { logger.info("Test failed"); }
}

}
