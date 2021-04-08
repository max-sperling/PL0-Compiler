/**
 * \author Max Sperling
 */

#include "../test/pl0compiler/CompilerTest.hpp"

int main()
{
    const pl0compiler::common::Logger logger(pl0compiler::common::Logger::Level::Info);
    pl0compiler::CompilerTest compTest(logger);

    std::string srcCode = "var a;\nbegin\n\ta:=0;\n\twhile a<7 do\n\tbegin\n\t\ta:=a+1;\n\t\t!a\n\tend\nend.";
    std::string binCode = "01000000172b000000040003000006000007000000060100121a12000300000000000602000c070000"
                          "000819ffffffe4ffffffff18000000000700000001000000";

    compTest.exec(srcCode, binCode);

    return 0;
}
