#include "LoggerFactory.h"

Logger* LoggerFactory::createLogger(std::string loggerName) {
	
	Logger* logger = new Logger();
	std::string fileName = "MPK-Log-" + loggerName + ".log";
	std::string filePath = "Log";
	LogPersistService* logPersistService = new LogPersistService(filePath, fileName);
	logPersistService->setmaxBytes(5000);
	logger->setlogPersistSerivce(logPersistService);
	logger->setLoggerId(loggerName);
	logger->setLogLevel(Error);
	//TODO: GET Log Level / Settings from CONFIG
	//TODO: Create factory 
	logPersistService->setlogLevel(Error);

	return logger;
}

LoggerFactory::LoggerFactory() {
	//TODO: GET Config form Init Unit
}

