#include "MessageQueue.h"
#include "ThreadMutexGuard.h"
#ifndef STATICQUEUE_H
#define STATICQUEUE_H


class StaticQueue : public MessageQueue {

private:
	/*One Mutex for Read and Write because of FIFO*/
	ThreadMutex* threadLockMessage;
	~StaticQueue();
public:
	StaticQueue(size_t maxCount, size_t slotLen, long uid, Logger* logger);

	size_t addMessage(unsigned char* message, size_t size);

	Message* readMessage();

	static const size_t absoluteMaxSlotLen = 1000;

private:
	int initFIFO();
};

#endif
