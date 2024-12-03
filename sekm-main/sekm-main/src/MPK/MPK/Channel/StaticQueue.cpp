#include "StaticQueue.h"

StaticQueue::StaticQueue(size_t maxCount, size_t slotLen, long uid, Logger* logger) :MessageQueue(maxCount, slotLen, uid, logger) {
	threadLockMessage = new ThreadMutex;
	initFIFO();

}
StaticQueue::~StaticQueue() {
	delete threadLockMessage;
}

size_t StaticQueue::addMessage(unsigned char* message, size_t size) {

	ThreadMutexGuard threadGuard(*threadLockMessage);
	{if (&threadGuard); };

	// Check if queue is full
	if (count >= maxCount) {
		threadGuard.release();
		return -1;
	}
	
	// Check if message to long
	bool cutState = false;
	if (size > slotLen) {
		fifo[writeAt]->size = slotLen;
		fifo[writeAt]->cutState = true;
		cutState = true;
	}
	else {
		fifo[writeAt]->size = size;
	}

	// get timestamp
	fifo[writeAt]->timestamp 
		= std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();

	// Copy message in queue
	memcpy(fifo[writeAt]->data, message, fifo[writeAt]->size);
	
	// Counter managment
	count++;
	if (++writeAt >= maxCount) writeAt = 0;

	threadGuard.release();

	if (cutState) return slotLen;
	return 0;
}

Message* StaticQueue::readMessage() {
	ThreadMutexGuard threadGuard(*threadLockMessage);
	{if (&threadGuard); };

	// Check if queue is empty
	if (count <= 0) {
		threadGuard.release();
		return nullptr;
	}

	// Read message
	Message* msg = new Message(fifo[readAt]->size);
	if (Message::copyMessage(msg, fifo[readAt])) return nullptr;
	count--;

	logger->info("Read Message from userid: " + std::to_string(uid));

	if (++readAt >= maxCount) readAt = 0;
	threadGuard.release();

	return msg;
}

int StaticQueue::initFIFO() {
	for (auto i = 0; i < maxCount; i++) {
		fifo[i] = mf.createMessage(slotLen);
		// Abort if memory could not be created
		if (fifo[i]->getData() == nullptr) return -1;
	}
	return 0;
}