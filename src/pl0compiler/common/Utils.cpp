/**
 * \author Max Sperling
 */

#include "Utils.hpp"

#include <sstream>
#include <iomanip>

namespace pl0compiler { namespace common {

std::string toString(const std::deque<char>& binary)
{
    std::stringstream ss;
    for (const auto& byte : binary)
    {
        ss << std::setfill('0') << std::setw(2) << std::hex << +byte;
    }
    return ss.str();
}

} }
