#include "../Logger/Logger.h"
#include "Config.h"

#include "json.hpp"

#include <string.h>
#include <string>
#include <fstream>
#include <iomanip>

#ifndef INITIALIZATION_CONFIGHANDLER_H
#define INITIALIZATION_CONFIGHANDLER_H


class ConfigHandler {
public:
	ConfigHandler::ConfigHandler(std::string configFileName);
	Config *readConfig();
	void writeConfig(Config *config);
private:
	std::string configFileName;
	Logger logger;

	nlohmann::json readFile(std::string filename);
	void writeFile(nlohmann::json);
	int readChannel(nlohmann::json* json, Config* config);
	bool ConfigHandler::checkContent(nlohmann::json::iterator it);
};


#endif
