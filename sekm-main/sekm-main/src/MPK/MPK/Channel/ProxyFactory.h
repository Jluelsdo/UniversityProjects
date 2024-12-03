#include "SenderProxy.h"
#include "RecieverProxy.h"

#ifndef PROXYFACTORY_H
#define PROXYFACTORY_H


class ProxyFactory {


public:
	SenderProxy* createSenderProxy(Channel** channel);

	RecieverProxy* createRecieverProxy(Channel** channel, size_t recieverSlotLen);
};

#endif
