/**
 * \author Max Sperling
 */

#include "Logger.hpp"

#include <iostream>

namespace pl0compiler { namespace common {

Logger::Logger(const Level level) : m_level(level) {}

void Logger::error(const std::string& str) const
{
    write(Level::Error, str);
}

void Logger::info(const std::string& str) const
{
    write(Level::Info, str);
}

void Logger::debug(const std::string& str) const
{
    write(Level::Debug, str);
}

void Logger::write(const Level level, const std::string& str) const
{
    if (m_level >= level) { std::cout << str << std::endl; }
}

} }
