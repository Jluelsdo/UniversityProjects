#include "Channel.h"
#ifndef CHANNELFACTORY_H
#define CHANNELFACTORY_H

class ChannelFactory {


public:
	Channel* createChannel(long kid, bool flagDynamicQueue, bool flagMultiReciever);
};

#endif
