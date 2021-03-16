#pragma once
/************************/
/* Author: Max Sperling */
/************************/

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

	void error(std::string const & str);
    void info(std::string const & str);
    void debug(std::string const & str);

    void write(Level level, std::string const & str);

private:
	bool allowed(Logger::Level level);

	Level const m_level;
};

} }
