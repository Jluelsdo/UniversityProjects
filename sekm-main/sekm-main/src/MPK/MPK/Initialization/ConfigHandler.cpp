#include "ConfigHandler.h"

ConfigHandler::ConfigHandler(std::string configFileName) {
	this->configFileName = configFileName;
}

Config *ConfigHandler::readConfig() {
	nlohmann::json json;
	Config* config = new Config();
	json = readFile(configFileName);
	if (json == NULL) return nullptr;
	int err = readChannel(&json, config);
	if (err == 0) return nullptr;
	return config;
}

void ConfigHandler::writeConfig(Config *config) {
	nlohmann::json json;
	std::list<ChannelConfig*>::iterator channelIt;
	std::list <ChannelConfig*> *channelList = config->channelList;
	nlohmann::json channelListJSON = nlohmann::json::array();
	
	for (channelIt = channelList->begin(); channelIt != channelList->end(); channelIt++) {
		nlohmann::json channelJSON;
		channelJSON["cid"] = (*channelIt)->kid;
		channelJSON["slotCount"] = (*channelIt)->slotCount;
		channelJSON["slotLength"] = (*channelIt)->slotLength;
		channelJSON["flagMultiReciever"] = (*channelIt)->flagMultiReciever;
		channelJSON["flagDynamicQueue"] = (*channelIt)->flagDynamicQueue;
		channelJSON["flagDelete"] = (*channelIt)->flagDelete;
		channelListJSON.push_back(channelJSON);
	}
	json["channel"] = channelListJSON;
	
	writeFile(json);
}

nlohmann::json ConfigHandler::readFile(std::string filename) {
	nlohmann::json json;
	try {
		std::ifstream inputstream(filename);
		inputstream >> json;
	}
	catch (const std::ifstream::failure& e) {
		return NULL;
	}
	catch (nlohmann::json::parse_error& ex) {
		return NULL;
	}
	return json;
}

void ConfigHandler::writeFile(nlohmann::json json) {
	try {
		std::ofstream out(this->configFileName);
		out << std::setw(4) << json << std::endl;
	}
	catch (const std::ofstream::failure& e) {
		throw "Fehler beim schreiben der Konfigurationsdatei";
	}
}

int ConfigHandler::readChannel(nlohmann::json* json, Config* config) {
	nlohmann::json channelListJSON;
	if (json->contains("channel")) {
		channelListJSON = json->find("channel").value();
		if (channelListJSON.is_array()) {
			for (nlohmann::json::iterator it = channelListJSON.begin(); it != channelListJSON.end(); ++it) {
				if (checkContent(it)) {
					ChannelConfig* channel = new ChannelConfig();

					channel->kid = it->find("cid")->get<int>();
					channel->slotCount = it->find("slotCount")->get<int>();
					channel->slotLength = it->find("slotLength")->get<int>();
					channel->flagMultiReciever = it->find("flagMultiReciever")->get<bool>();
					channel->flagDynamicQueue = it->find("flagDynamicQueue")->get<bool>();
					channel->flagDelete = it->find("flagDelete")->get<bool>();

					config->channelList->push_back(channel);
				}
				else return 0;
			}
		}
		else return 0;
		return 1;
	}
	else return 0;
}
bool ConfigHandler::checkContent(nlohmann::json::iterator it) {
	if (it->contains("cid") && it->contains("slotCount") && it->contains("slotLength") &&
		it->contains("flagMultiReciever") && it->contains("flagDynamicQueue") &&
		it->contains("flagDelete") && (*it)["cid"].is_number_integer() &&
		(*it)["slotCount"].is_number_integer() && (*it)["slotLength"].is_number_integer() &&
		(*it)["flagMultiReciever"].is_boolean() && (*it)["flagDynamicQueue"].is_boolean() &&
		(*it)["flagDelete"].is_boolean()) {
		return true;
	}
	else return false;
}


