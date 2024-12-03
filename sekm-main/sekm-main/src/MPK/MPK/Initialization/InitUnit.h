#include "../Logger/Logger.h"
#include "Config.h"
#include "ConfigHandler.h"
#include "Config.h"
#include "../Channel/ChannelRegistry.h"
#include "../Logger/LoggerRegistry.h"

#include <string>

#ifndef INITIALIZATION_INITUNIT_H
#define INITIALIZATION_INITUNIT_H


class InitUnit {

private:
	static InitUnit* instance;
	Logger *logger;
	Config *config;
	ThreadMutex* threadLockInitReinit;

	void init();

protected:
	InitUnit();
	~InitUnit();

public:
	static InitUnit& getInstance();
	Channel** initChannel(long cid, bool flagDynamicQueue, bool flagMultiReciever);
	int reinitChannelById(long cid);
	void setConfig(Config* config);
	Logger* getLogger();
	void reinitAllChannel();

};

#endif
