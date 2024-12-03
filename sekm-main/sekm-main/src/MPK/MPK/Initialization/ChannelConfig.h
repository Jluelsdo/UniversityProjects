#ifndef INITIALIZATION_CHANNELCONFIG_H
#define INITIALIZATION_CHANNELCONFIG_H

#include <list>

struct ChannelConfig {

public:
	long kid;
	size_t slotCount;
	size_t slotLength;
	int cVersion;
	bool flagMultiReciever;
	bool flagDynamicQueue;
	bool flagDelete;
	std::list<int> receivers;
};


#endif
