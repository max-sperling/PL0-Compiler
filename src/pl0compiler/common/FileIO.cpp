/************************/
/* Author: Max Sperling */
/************************/

#include "FileIO.hpp"

#include <fstream>

namespace pl0compiler { namespace common {

FileIO::FileIO(std::string const & pl0File, std::string const & cl0File)
    : m_pl0File(pl0File), m_cl0File(cl0File) {}

bool FileIO::read(std::string & str) const
{
    std::ifstream ifs(m_pl0File);
    if (ifs.fail()) return false;
    str = {std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()};
    ifs.close();
    return true;
}

bool FileIO::write(std::deque<char> const & bin) const
{
    std::ofstream ofs(m_cl0File, std::ios_base::binary);
    if (ofs.fail()) return false;
    copy(bin.begin(), bin.end(), std::ostreambuf_iterator<char>(ofs));
    ofs.close();
    return true;
}

} }
