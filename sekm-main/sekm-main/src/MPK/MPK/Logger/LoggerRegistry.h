#include "Logger.h"
#include <list>
#include "LoggerFactory.h"
#ifndef LOGGER_LOGGERREGISTRY_H
#define LOGGER_LOGGERREGISTRY_H

class LoggerRegistry {

protected:
	LoggerRegistry();
	LoggerRegistry(const LoggerRegistry&); 
	LoggerRegistry& operator= (const LoggerRegistry&);
	~LoggerRegistry();

private:
	LoggerFactory* LoggerFactory;
	static LoggerRegistry* instance;
	std::list<Logger*> loggerList;


public:
	static LoggerRegistry* getLoggerRegistry();
	Logger* getLogger(std::string uuid);
	bool deleteLogger(Logger* logger);
};


#endif
