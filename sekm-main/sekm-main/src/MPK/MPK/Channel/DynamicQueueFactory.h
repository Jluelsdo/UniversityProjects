#include "DynamicQueue.h"
#include "AbstractMessageQueueFactory.h"
#ifndef DYNAMICQUEUEFACTORY_H
#define DYNAMICQUEUEFACTORY_H

class DynamicQueueFactory : public AbstractMessageQueueFactory {

public:

	virtual MessageQueue* createMessageQueue(size_t maxCount, size_t slotLen, size_t uid, Logger* logger);

};

#endif
