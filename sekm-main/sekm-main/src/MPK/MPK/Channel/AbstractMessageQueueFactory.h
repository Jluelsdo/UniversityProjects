#include "MessageQueue.h"
#ifndef ABSTRACTMESSAGEQUEUEFACTORY_H
#define ABSTRACTMESSAGEQUEUEFACTORY_H



class AbstractMessageQueueFactory {


public:
	virtual MessageQueue* createMessageQueue(size_t maxCount, size_t slotLen, size_t uid, Logger* logger) = 0;

};

#endif
