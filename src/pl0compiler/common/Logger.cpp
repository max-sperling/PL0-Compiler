/************************/
/* Author: Max Sperling */
/************************/

#include "Logger.hpp"

#include <iostream>

namespace pl0compiler { namespace common {

Logger::Logger(Level const level) : m_level(level) {}

void Logger::error(std::string const &str) const
{
    write(Level::Error, str);
}

void Logger::info(std::string const &str) const
{
    write(Level::Info, str);
}

void Logger::debug(std::string const &str) const
{
    write(Level::Debug, str);
}

void Logger::write(Level const level, std::string const &str) const
{
	if (m_level >= level) { std::cout << str << std::endl; }
}

} }
