#pragma once
/**
 * \author Max Sperling
 */

#include <string>
#include <deque>

namespace pl0compiler { namespace common {

class Logger
{
public:
    enum class Level
    {
        Error,
        Info,
        Debug
    };

    Logger(Level const level);

    void error(const std::string& str) const;
    void info(const std::string& str) const;
    void debug(const std::string& str) const;

    void write(const Level level, const std::string& str) const;

private:
    const Level m_level;
};

} }
