#include "Channel.h"

Channel::Channel(long kid, bool flagDynamicQueue, bool flagMultiReciever) {
	threadLock = new ThreadMutex;

	this->flagDynamicQueue = flagDynamicQueue;
	this->flagMultiReciever = flagMultiReciever;
	this->kid = kid;
	this->flagDelete = false;
	this->maxChannelSlotLen = StaticQueue::absoluteMaxSlotLen;
	this->slotCount = 1;
	this->cVersion = 0;
	
	if (flagDynamicQueue) mqFactory =  new DynamicQueueFactory;
	else mqFactory = new StaticQueueFactory;
	
	std::string logName = "channel-" + std::to_string(kid);
	logger = LoggerRegistry::getLoggerRegistry()->getLogger(logName);
	logger->info("Channel created");
}

Channel::~Channel(){
	delete threadLock;

	logger->info("Channel deleted/reinit, Version: " + std::to_string(cVersion));
	

	for (auto element : messageQueueList) {
		delete element;
	}
	messageQueueList.clear();

}

ChannelConfig Channel::getChannelConfig() {
	ChannelConfig cc;
	cc.kid = kid;
	cc.flagDelete = flagDelete;
	cc.flagDynamicQueue = flagDynamicQueue;
	cc.flagMultiReciever = flagMultiReciever;
	cc.slotCount = slotCount;
	cc.slotLength = maxChannelSlotLen;
	cc.cVersion = cVersion;
	for (auto element : messageQueueList) {
		cc.receivers.push_back(element->getUID());
	}
	return cc;
}

/**
* Create MessageQueue
* Returns 
* - MessageQueue ptr when succssesful
* - nullptr when failed
*/
MessageQueue* Channel::createMessageQueue(size_t recieverSlotLen, long uid) {

	ThreadMutexGuard threadGuard(*threadLock);
	{if (&threadGuard); };

	if (flagMultiReciever || messageQueueList.size() == 0) {

		MessageQueue* msg = mqFactory->createMessageQueue(slotCount, recieverSlotLen, uid, logger);
		messageQueueList.push_back(msg);

		threadGuard.release();

		std::string logMessage = "New messageQueue created for uid " + std::to_string(uid);
		logger->info(logMessage);

		return msg;
	}
	threadGuard.release();

	logger->error("Can't create messageQueue");

	return nullptr;
}

/**
* Looking for messageQueue by User ID
* Returns
* - MessageQueue ptr when succssesful
* - nullptr when failed
*/
MessageQueue* Channel::getMessageQueueByUID(size_t uid) {
	for (auto mq : messageQueueList) {
		if (mq->getUID() == uid) return mq;
	}
	return nullptr;
}

bool Channel::checkMessageQueueListEmpty() {
	for (auto element : messageQueueList) {
		if (element->getCount()) return false;
	}
	return true;
}

int Channel::addMessage(unsigned char* message, size_t size) {
	size_t state = 0;
	for (auto element : messageQueueList) {
		element->addMessage(message, size);
	}


	if (state < 0) {
		logger->error("Got Message but state < " + std::to_string(state));
		return state;
	}
	logger->info("got new message");

	if (size > maxChannelSlotLen) {
		logger->logMessage("PUT", message, size, true);
		return maxChannelSlotLen;
	}
	logger->logMessage("PUT", message, size, false);

	return 0;
}