#include "StaticQueue.h"
#include "AbstractMessageQueueFactory.h"

#ifndef STATICQUEUEFACTORY_H
#define STATICQUEUEFACTORY_H

class StaticQueueFactory : public AbstractMessageQueueFactory {
public:

	virtual MessageQueue* createMessageQueue(size_t maxCount, size_t slotLen, size_t uid, Logger* logger);

};

#endif


