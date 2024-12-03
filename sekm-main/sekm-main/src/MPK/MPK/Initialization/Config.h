#include <list>
#include "ChannelConfig.h"
#include "../Logger/LogLevel.h"

#ifndef INITIALIZATION_CONFIG_H
#define INITIALIZATION_CONFIG_H


class Config {
public:
	Config();
	std::list <ChannelConfig*> *channelList;
	struct LogLevel {
	};

private:
	LogLevel defaultLogLevel;
		};

#endif