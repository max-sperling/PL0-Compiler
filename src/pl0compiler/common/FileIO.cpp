/**
 * \author Max Sperling
 */

#include "FileIO.hpp"

#include <fstream>

namespace pl0compiler { namespace common {

FileIO::FileIO(const std::string& file) : m_file(file) {}

bool FileIO::read(std::string& str) const
{
    std::ifstream ifs(m_file);
    if (ifs.fail()) { return false; }
    str = {std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()};
    ifs.close();
    return true;
}

bool FileIO::write(const std::deque<char>& bin) const
{
    std::ofstream ofs(m_file, std::ios_base::binary);
    if (ofs.fail()) { return false; }
    copy(bin.begin(), bin.end(), std::ostreambuf_iterator<char>(ofs));
    ofs.close();
    return true;
}

} }
