/************************/
/* Author: Max Sperling */
/************************/

#include "Utils.hpp"

#include <sstream>
#include <iomanip>

namespace pl0compiler { namespace common {

std::string toString(const std::deque<char>& bin)
{
    std::stringstream ss;
    for (auto &b : bin)
    {
        ss << std::setfill('0') << std::setw(2) << std::hex << +b;
    }
    return ss.str();
}

} }
