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
    void runTest(const string& srcCode, const string& expectedBinCode);
};

}
