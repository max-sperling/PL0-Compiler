/**
 * \author Max Sperling
 */

#include "../test/pl0compilertest/CompilerTest.hpp"

int main()
{
    std::string srcCode = "var a;\nbegin\n\ta:=0;\n\twhile a<7 do\n\tbegin\n\t\ta:=a+1;\n\t\t!a\n\tend\nend.";
    std::string binCode = "01000000172b000000040003000006000007000000060100121a12000300000000000602000c070000"
                          "000819ffffffe4ffffffff18000000000700000001000000";

    pl0compilertest::CompilerTest compTest;
    compTest.runTest(srcCode, binCode);

    return 0;
}
