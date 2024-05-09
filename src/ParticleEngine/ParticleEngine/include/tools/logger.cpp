#include <iostream>

#include "tools/logger.h"

void Logger::log(LogType logType, std::string function, int line, std::string log)
{
	std::string LOG_PREFIX = "";
	std::string COLOR = "";

	switch (logType)
	{
	case LogType::INFO:
		LOG_PREFIX = "INFO";
		COLOR = GRAY;
		break;
	case LogType::SUCCESS:
		LOG_PREFIX = "SUCCESS";
		COLOR = GREEN;
		break;
	case LogType::WARNING:
		LOG_PREFIX = "WARNING";
		COLOR = YELLOW;
		break;
	case LogType::ERROR:
		LOG_PREFIX = "ERROR";
		COLOR = RED;
		break;
	case LogType::FATAL:
		LOG_PREFIX = "FATAL";
		COLOR = DARK_RED;
		break;
	}

	std::cout << COLOR << "[" << LOG_PREFIX << "] " << "(" << function << ":" << line << ")" << " " << log << std::endl;
	std::cout << RESET; // reset color
}