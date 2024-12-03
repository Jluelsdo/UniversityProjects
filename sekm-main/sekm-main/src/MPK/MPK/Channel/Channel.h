#include "../Initialization/ChannelConfig.h"
#include "../Logger/LoggerRegistry.h"
#include <list>
#include "DynamicQueueFactory.h"
#include "StaticQueueFactory.h"
#include "ThreadMutexGuard.h"
#ifndef CHANNEL_H
#define CHANNEL_H

class Channel {

private:
	long kid;
	/**
	 * Flag is set when chanel should be deleted. Doesn't accept new messages when true. When true then check if any message queue has any message left when recieverproxy tries to take out a message check if this was the last message.
	 */
	bool flagDelete;
	/**
	 * False = Use a staticQueue as MessageQueues, True = Use a DynamicQueue
	 */
	bool flagDynamicQueue;
	/**
	 * Either set Channel as a single reciever (false) or open it for multiple reciever (true)
	 */
	bool flagMultiReciever;

	int cVersion;
	size_t maxChannelSlotLen;
	size_t slotCount;
	std::list<MessageQueue*> messageQueueList;
	AbstractMessageQueueFactory* mqFactory;
	Logger* logger;

	 ThreadMutex* threadLock;

public:
	Channel(long kid, bool flagDynamicQueue, bool flagMultiReciever);

	// TODO: Destructor is missing
	~Channel();

public:
	ChannelConfig getChannelConfig();

	/**
	* Create MessageQueue
	* Returns
	* - MessageQueue ptr when succssesful
	* - nullptr when failed
	*/
	MessageQueue* createMessageQueue(size_t recieverSlotLen, long uid);
	
public: 
	// Getter and SettergetChannelID
	long getKID() const { return kid; }
	void setFlagDelete(bool flagDelete) { this->flagDelete = flagDelete; }
	bool getFlagDelete() {return flagDelete;}
	bool getFlagDynamicQueue() { return flagDynamicQueue; }
	void setFlagMultiReciever(bool flagMultiReciever) {this->flagMultiReciever = flagMultiReciever;}
	bool getFlagMultiReciever() {return flagMultiReciever;}
	void setMaxChannelSlotLen(size_t maxChannelSlotLen) { this->maxChannelSlotLen = maxChannelSlotLen;}
	size_t getMaxChannelSlotLen() {return maxChannelSlotLen;}
	void setSlotCount(size_t slotCount) { this->slotCount = slotCount; }
	size_t getSlotCount() { return slotCount; }
	int getCVersion() { return cVersion; }
	void setCVersion(int cVersion) { this->cVersion = cVersion; }

	/**
	* Looking for messageQueue by User ID
	* Returns
	* - MessageQueue ptr when succssesful
	* - nullptr when failed
	*/
	MessageQueue* getMessageQueueByUID(size_t uid);

	/**
	* Check if alle message queues are empty
	*/
	bool checkMessageQueueListEmpty();

	/**
	* Add a message to all message queues
	*/
	int addMessage(unsigned char* message, size_t size);
};

#endif
