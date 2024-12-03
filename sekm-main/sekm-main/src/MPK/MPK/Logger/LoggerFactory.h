#include "Logger.h"
#include "../Initialization/Config.h"
#include <string>


#ifndef LOGGER_LOGGERFACTORY_H
#define LOGGER_LOGGERFACTORY_H


class LoggerFactory {


public:
	Logger* createLogger(std::string loggerName);

	LoggerFactory();

};


#endif
