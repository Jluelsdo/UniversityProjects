#include "LoggerRegistry.h"
#include "LogLevel.h"

LoggerRegistry::LoggerRegistry(void) { 
}
LoggerRegistry::~LoggerRegistry(void) {
}
LoggerRegistry* LoggerRegistry::instance = 0;

LoggerRegistry* LoggerRegistry::getLoggerRegistry() { // Erzeugung Exemplar
	if (instance == 0) {
		instance = new LoggerRegistry;
	}
	return (instance);
}

Logger* LoggerRegistry::getLogger(std::string sid) {

	for (auto logger : loggerList) {
		if (logger->getLoggerId() == sid) {
			logger->info("Logger allready present");
			return logger;
		}
	}
	Logger* logger = new Logger();
	logger = LoggerFactory->createLogger(sid);
	
	loggerList.push_back(logger);

	return logger;
}
bool LoggerRegistry::deleteLogger(Logger* loggerToDelete) {

	for (auto logger : loggerList) {
		if (logger == loggerToDelete) {
			delete logger;
			return true;
		}
	}
	return false;
}
