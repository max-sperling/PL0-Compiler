/**
 * \author Max Sperling
 */

#include "Compiler.hpp"

#include "Tokenizer.hpp"
#include "Generator.hpp"
#include "common/Token.hpp"
#include "common/Exception.hpp"

namespace pl0compiler {

Compiler::Compiler(const common::Logger& logger) : m_logger(logger) {}

bool Compiler::exec(std::string& srcCode, std::deque<char>& binCode)
{
    std::deque<common::Token> token;
    try
    {
        Tokenizer tokenizer;
        tokenizer.exec(srcCode, token);
    }
    catch (...)
    {
        m_logger.error("Error while Tokenization");
        return false;
    }

    binCode.clear();
    try
    {
        Generator generator;
        generator.exec(token, binCode);
    }
    catch (common::Exception &excp)
    {
        m_logger.error("Error while Generating");
        m_logger.error(excp.getError());
        return false;
    }

    return true;
}

}
