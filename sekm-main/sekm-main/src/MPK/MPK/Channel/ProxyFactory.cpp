#include "ProxyFactory.h"
#include "Channel.h"
#include "SenderProxy.h"
#include "RecieverProxy.h"

SenderProxy* ProxyFactory::createSenderProxy(Channel** channel) {
	SenderProxy* senderProxy = new SenderProxy(channel);
	return senderProxy;
}

RecieverProxy* ProxyFactory::createRecieverProxy(Channel** channel, size_t recieverSlotLen) {
	RecieverProxy* recieverProxy = new RecieverProxy(channel, recieverSlotLen);
	return recieverProxy;
}

