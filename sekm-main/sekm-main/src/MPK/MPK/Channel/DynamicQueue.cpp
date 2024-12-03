#include "DynamicQueue.h"

DynamicQueue::DynamicQueue(size_t maxCount, size_t slotLen, long uid, Logger* logger):MessageQueue(maxCount, slotLen, uid, logger) {
	threadLockMessage = new ThreadMutex;
}
DynamicQueue::~DynamicQueue() {
	delete threadLockMessage;
}

size_t DynamicQueue::addMessage(unsigned char* message, size_t size) {
	// Check if queue is full
	ThreadMutexGuard threadGuard(*threadLockMessage);
	{if (&threadGuard); };

	if (count >= maxCount) {
		threadGuard.release();
		return -1;
	}

	// Check if message to long and create message
	bool cutState = false;
	if (size > slotLen) {

		fifo[writeAt] = mf.createMessage(slotLen);
		fifo[writeAt]->size = slotLen;
		fifo[writeAt]->cutState = true;
		cutState = true;
	}
	else {

		fifo[writeAt] = mf.createMessage(size);
		fifo[writeAt]->size = size;
	}

	// Abort if memory could not be created
	if (fifo[writeAt]->getData() == nullptr) return -2;

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

Message* DynamicQueue::readMessage() {
	// Check if queue is empty
	ThreadMutexGuard threadGuard(*threadLockMessage);
	{if (&threadGuard); };

	if (count <= 0) {
		threadGuard.release();
		return nullptr;
	}

	// Read message
	Message *msg = new Message(fifo[readAt]->size);
	if (Message::copyMessage(msg, fifo[readAt])) return nullptr;
	delete fifo[readAt];
	fifo[readAt] = nullptr;
	count--;

	logger->info("Read Message from userid: " + std::to_string(uid));

	if (++readAt >= maxCount) readAt = 0;



	threadGuard.release();

	return msg;
}