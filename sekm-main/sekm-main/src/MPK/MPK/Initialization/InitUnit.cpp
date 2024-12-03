#include "InitUnit.h"
/// Singleton
InitUnit* InitUnit::instance = nullptr;
InitUnit& InitUnit::getInstance() {
	if (!instance){
		instance = new InitUnit();
		instance->init();
	}
	return *instance;
}

InitUnit::InitUnit() {
}

InitUnit::~InitUnit() {
	delete threadLockInitReinit;
	delete logger;
};

void InitUnit::init() {
//lock init()
threadLockInitReinit = new ThreadMutex;
ThreadMutexGuard threadGuard(*threadLockInitReinit);
{if (&threadGuard); };
//create Logger "MPK" (MPK Logger)
LoggerRegistry* loggerRegistry;
loggerRegistry = LoggerRegistry::getLoggerRegistry();
this->logger = loggerRegistry->getLogger("MPK");
//load config
ConfigHandler* confHandler = new ConfigHandler("config.json");
this->config = nullptr;
this->config = confHandler->readConfig();
if (!(this->config == nullptr)) {
	std::list<ChannelConfig*>::iterator it;
	bool found = false;
	for (it = this->config->channelList->begin(); it != this->config->channelList->end(); it++) {
		Channel** channel = ChannelRegistry::getInstance().addChannel((*it)->kid, (*it)->flagDynamicQueue, (*it)->flagMultiReciever);
		this->logger->info("Initialized Channel from Config: " + std::to_string((*it)->kid));
	}
}
else this->logger->error("Error reading config. No channels initalized");
//TBD mpk erstellen mit channelregistry(?) connectunit (?)
this->logger->info("InitUnit initialized");
delete confHandler;
threadGuard.release();
}

Channel** InitUnit::initChannel(long cid, bool flagDynamicQueue, bool flagMultiReciever) {
	Channel** channel = ChannelRegistry::getInstance().addChannel(cid, flagDynamicQueue, flagMultiReciever);
	return channel;
}

int InitUnit::reinitChannelById(long cid) {
	Channel **channel = (ChannelRegistry::getInstance().getChannelByID(cid));
	if (channel == nullptr) {
		this->logger->error("Channel not found. CID:" + std::to_string(cid));
		return -1;
	}
	ChannelConfig channelConf = (*(channel))->getChannelConfig();
	int err = ChannelRegistry::getInstance().reinitChannel(channelConf);
	if (err == -1) {
		this->logger->error("Error reinitializing Channel: " + std::to_string(cid));
		return -1;
	}
	this->logger->info("Reinitialized Channel: " + std::to_string(cid));
	return 0;
}

void InitUnit::reinitAllChannel() {
	ChannelRegistry::getInstance().reinitAllChannel();
}

//setConfig is used to set a non-default config file
void InitUnit::setConfig(Config* config) {
	this->config = config;
}

Logger* InitUnit::getLogger() {
	return this->logger;
}
