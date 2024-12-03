#include "ChannelFactory.h"

Channel* ChannelFactory::createChannel(long kid, bool flagDynamicQueue, bool flagMultiReciever) {
	Channel *newChannel = new Channel(kid, flagDynamicQueue, flagMultiReciever);
	return newChannel;
	
}
