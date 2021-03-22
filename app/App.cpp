/**
 * \author Max Sperling
 */

#include "../src/pl0compiler/common/Logger.hpp"
#include "../src/pl0compiler/common/FileIO.hpp"
#include "../src/pl0compiler/common/Utils.hpp"
#include "../src/pl0compiler/Compiler.hpp"

int main(int argc, char *argv[])
{
    const pl0compiler::common::Logger logger(pl0compiler::common::Logger::Level::Info);
    pl0compiler::Compiler comp(logger);

    if (argc != 3)
    {
        logger.error("Usage: program <pl0-File> <cl0-File>\n");
        return 1;
    }

    std::string srcCode = "";

    if (!pl0compiler::common::FileIO::read(argv[1], srcCode))
    {
        logger.error("Error while reading File");
        return 2;
    }

    std::deque<char> binCode;

    if (!comp.exec(srcCode, binCode))
    {
        logger.error("Error while compiling");
        return 3;
    }

    logger.info(pl0compiler::common::toString(binCode));

    if (!pl0compiler::common::FileIO::write(argv[2], binCode))
    {
        logger.error("Error while writing File");
        return 4;
    }

    return 0;
}
