#include "MessageQueue.h"

MessageQueue::MessageQueue(size_t maxCount, size_t slotLen, long uid, Logger* logger) {
	this->maxCount = maxCount;
	this->slotLen = slotLen;
	this->uid = uid;
	this->logger = logger;
	fifo.resize(maxCount);
}

MessageQueue::~MessageQueue() {
	for (auto element : fifo) {
		if(element != nullptr) delete element;
	}
	fifo.clear();
}