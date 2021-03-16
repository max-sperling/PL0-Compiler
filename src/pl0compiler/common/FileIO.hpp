#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <string>
#include <deque>

namespace pl0compiler { namespace common {

class FileIO
{
public:
    FileIO(const std::string& pl0File, const std::string& cl0File);

    /**
     * @param[out] str ... contains read pl0 code
     */
    bool read(std::string& str) const;

    /**
     * @param[in] bin ... contains cl0 code to write
     */
    bool write(const std::deque<char>& bin) const;

private:
    std::string const m_pl0File;
    std::string const m_cl0File;
};

} }
