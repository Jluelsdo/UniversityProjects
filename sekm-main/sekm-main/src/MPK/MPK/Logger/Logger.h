
#include "LogPersistService.h"
#include "LogEntryMessage.h"
#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H


class Logger {

private:
	LogPersistService* logPersistSerivce;
	std::string id;
	LogLevel logLevel = Debug;
	bool logMessageEnabled = true;

public:

	void logMessage(std::string method, unsigned char* message, size_t size, bool shorted);
	
	void setLogLevel(LogLevel logLevel);
	
	void setLoggerId(std::string);

	void setlogPersistSerivce(LogPersistService* logPersistSerivce);

	void info(std::string message);

	void warning(std::string message);

	void error(std::string message);

	void debug(std::string message);

	std::string getLoggerId();
};


#endif
