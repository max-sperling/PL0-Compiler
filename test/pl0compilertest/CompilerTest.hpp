#pragma once
/**
 * \author Max Sperling
 */

#include <string>
#include <deque>

namespace pl0compilertest {

class CompilerTest
{
public:
    void runTest(std::string& srcCode, const std::string& expectedBinCode);
};

}
