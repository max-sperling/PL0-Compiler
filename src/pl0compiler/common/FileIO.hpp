#pragma once
/**
 * \author Max Sperling
 */

#include <string>
#include <deque>

namespace pl0compiler { namespace common {

class FileIO
{
public:
    /**
     * @param[in]  file ... file to read
     * @param[out] str  ... read content
     */
    static bool read(const std::string& file, std::string& str);

    /**
     * @param[in] file ... file to write
     * @param[in] bin  ... content to write
     */
    static bool write(const std::string& file, const std::deque<char>& bin);
};

} }
