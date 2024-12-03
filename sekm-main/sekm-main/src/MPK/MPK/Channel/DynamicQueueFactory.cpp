#include "DynamicQueueFactory.h"

MessageQueue* DynamicQueueFactory::createMessageQueue(size_t maxCount, size_t slotLen, size_t uid, Logger* logger) {
	return new DynamicQueue(maxCount, slotLen, uid, logger);
}
