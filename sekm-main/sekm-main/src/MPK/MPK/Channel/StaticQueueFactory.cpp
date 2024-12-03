#include "StaticQueueFactory.h"


MessageQueue* StaticQueueFactory::createMessageQueue(size_t maxCount, size_t slotLen, size_t uid, Logger* logger) {
	return new StaticQueue(maxCount, slotLen, uid, logger);
}
