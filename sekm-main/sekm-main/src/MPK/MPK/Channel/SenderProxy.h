#include "Channel.h"


#ifndef SENDERPROXY_H
#define SENDERPROXY_H

class SenderProxy {

private:
	Channel** channel;

public:
	/**
	 * Return:
	 *   0: all ok
	 *  -1: messageQueue is full
	 *  -2: memory could not be created
	 * -10: no channel
	 * -11: channel marked for deletion
	 *  >0: message is cuted to n bytes
	 */
	int addMessage(unsigned char* message, size_t size);

	SenderProxy(Channel** channel);
};

#endif
