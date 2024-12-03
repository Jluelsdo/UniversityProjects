#include "MessageFactory.h"
#include "ThreadMutex.h"
#include <vector>
#include <chrono>
#include "../Logger/Logger.h"
#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

class MessageQueue {

protected:
	std::vector<Message*> fifo;
	ThreadMutex lock;
	size_t count = 0;
	size_t maxCount = 0;
	size_t slotLen = 0;
	long uid = -1;

	size_t writeAt = 0;
	size_t readAt = 0;

	Logger* logger;

	MessageFactory mf;

public:
	MessageQueue(size_t maxCount, size_t slotLen, long uid, Logger* logger);
	~MessageQueue();
	/**
	 * Returns
	 * -2 when memory could not be created
	 * -1 when Message Queue is full
	 * 0 Message was added
	 * n, size of Message after it was cut in bytes
	 */
	virtual size_t addMessage(unsigned char* message, size_t size) = 0;

	/**
	* Returns 
	* nullptr when queue is empty
	*/
	virtual Message* readMessage() = 0;

	long getUID() { return uid; }

	size_t getCount() { return count; }

};

#endif
