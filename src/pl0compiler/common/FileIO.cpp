/**
 * \author Max Sperling
 */

#include "FileIO.hpp"

#include <fstream>

namespace pl0compiler { namespace common {

bool FileIO::read(const std::string& file, std::string& str)
{
    std::ifstream ifs(file);
    if (ifs.fail()) { return false; }
    str = {std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()};
    ifs.close();
    return true;
}

bool FileIO::write(const std::string& file, const std::deque<char>& bin)
{
    std::ofstream ofs(file, std::ios_base::binary);
    if (ofs.fail()) { return false; }
    copy(bin.begin(), bin.end(), std::ostreambuf_iterator<char>(ofs));
    ofs.close();
    return true;
}

} }
