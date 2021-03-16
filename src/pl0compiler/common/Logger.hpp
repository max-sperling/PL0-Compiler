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

	void error(std::string const &str) const;
    void info(std::string const &str) const;
    void debug(std::string const &str) const;

    void write(Level const level, std::string const &str) const;

private:
	Level const m_level;
};

} }
