/************************/
/* Author: Max Sperling */
/************************/

#include "Logger.hpp"

#include <iostream>

namespace pl0compiler { namespace common {

Logger::Logger(Level const level) : m_level(level) {}

void Logger::error(std::string const & str)
{
    write(Level::Error, str);
}

void Logger::info(std::string const & str)
{
    write(Level::Info, str);
}

void Logger::debug(std::string const & str)
{
    write(Level::Debug, str);
}

void Logger::write(Level level, std::string const & str)
{
	if (allowed(level)) { std::cout << str << std::endl; }
}

bool Logger::allowed(Level level)
{
	return (m_level >= level);
}

} }
