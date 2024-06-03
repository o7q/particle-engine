#pragma once

#include <iostream>

#define GRAY     "\033[37m"
#define GREEN    "\033[92m"
#define YELLOW   "\033[93m"
#define RED      "\033[91m"
#define DARK_RED "\033[31m"

#define RESET    "\033[0m"

class Logger {
public:
	enum class LogType {
		INFO,
		SUCCESS,
		WARNING,
		ERROR,
		FATAL
	};

	static void log(LogType, std::string, int, std::string);
};