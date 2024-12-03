#include "../Initialization/Config.h"
#include <string>
#include "LogLevel.h"
#ifndef LOGGER_LOGENTRY_H
#define LOGGER_LOGENTRY_H


class LogEntry {

private:
	LogLevel level;
	std::string message;
	long long timestamp;

public:
	LogEntry(LogLevel level, std::string message, long long timestamp);
	long long getTimestamp();
	std::string getMessage();
	

};


#endif
