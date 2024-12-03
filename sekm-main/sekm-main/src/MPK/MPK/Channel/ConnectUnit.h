#include "ProxyFactory.h"
#include "ChannelRegistry.h"


#ifndef CONNECTUNIT_H
#define CONNECTUNIT_H

class ConnectUnit {


public:
	RecieverProxy* connectReciever(long kid, size_t recieverSlotLen, size_t maxChannelSlotLen, bool flagDynamicQueue, bool flagMultiReciever, bool flagInitialize = true);

	RecieverProxy* connectReciever(long kid, size_t recieverSlotLenbool, bool flagInitialize = true);

	SenderProxy* connectSender(long kid, size_t maxChannelSlotLen, bool flagDynamicQueue, bool flagMultiReciever, bool flagInitialize = true);

	SenderProxy* connectSender(long kid, bool flagInitialize = true);

	void reinitChannel(int kid);

	void reinitAllChannel();
};

#endif
