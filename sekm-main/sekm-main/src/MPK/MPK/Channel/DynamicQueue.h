#include "Message.h"
#include "MessageQueue.h"
#include "ThreadMutexGuard.h"
#ifndef DYNAMICQUEUE_H
#define DYNAMICQUEUE_H

class DynamicQueue : public MessageQueue {

private:
	/*One Mutex for Reading and Writing into the FIFO*/
	ThreadMutex* threadLockMessage;
	~DynamicQueue();
public:
	DynamicQueue(size_t maxCount, size_t slotLen, long uid, Logger* logger);

	size_t addMessage(unsigned char* message, size_t size);

	Message* readMessage();
};

#endif
