#include "RecieverProxy.h"

RecieverProxy::RecieverProxy(Channel** channel, size_t recieverSlotLen) {
	this->channel = channel;
	this->uid = ChannelRegistry::getInstance().createUID();
	this->recieverSlotLen = recieverSlotLen;
	this->messageQueue = getMessageQueueFromChannel();
	this->callbackTranslator = defaultTranslator;
	this->cVersion = (*channel)->getCVersion();
}

/**
* Read next message from messageQueue and translate
* Returns:
* -1 then there is no channel
* -2 then there is no messageQueue
* -3 then there is no message
*/
int RecieverProxy::readMessage(void* msgOut) {
	// return if there is no channel
	if ((*channel) == nullptr) return -1;

	// Check if the channel version is the same
	if (cVersion != (*channel)->getCVersion()) {
		messageQueue = getMessageQueueFromChannel();
		cVersion = (*channel)->getCVersion();
	}

	// return if there is no messageQueue
	if (messageQueue == nullptr) {
		// Try to get messsageQueue from channel
		messageQueue = getMessageQueueFromChannel();
		if (messageQueue == nullptr) return -2;
	}

	// read message from messageQueue
	Message* msgIn = messageQueue->readMessage();
	
	// return if there is no message
	if (msgIn == nullptr) return -3;

	// Translate message
	callbackTranslator(msgIn->getData()
		, msgIn->getSize()
		, msgOut);

	// delete message
	delete msgIn;
	channelManagment();
	return 0;
}

int RecieverProxy::readMessageWait(void* message, long long timeout) {
	long long exitAt = std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count()
		+ timeout;
	int status;
	while (true) {
		status = readMessage(message);
		if (status == 0) break;
		if (status != -3) return status;
		if (exitAt < std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count())
			return -10;
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
	return 0;
}

/**
 * Calls deleteChannel from ChannelRegistery
 */
void RecieverProxy::deleteChannel() {
	(*channel)->setFlagDelete(true);
}

MessageQueue* RecieverProxy::getMessageQueueFromChannel() {
	MessageQueue* msg;
	// Try to get MessageQueue from User ID
	msg = (*channel)->getMessageQueueByUID(uid);
	
	// If there is no matching MessageQueue create one
	if (msg == nullptr) {
		msg = (*channel)->createMessageQueue(recieverSlotLen, uid);
	}

	return msg;
}

/**
* Channel Managment
* Delete channel if it is marked for deletion
* and every messageQueue is empty
*/
void RecieverProxy::channelManagment() {
	if ((*channel)->getFlagDelete()) {
		if (messageQueue == nullptr) return;
		if (messageQueue->getCount()) return;
		messageQueue = nullptr;
		if(!(*channel)->checkMessageQueueListEmpty()) return;
		ChannelRegistry::getInstance().deleteChannel((*channel)->getKID());
	}
}

void RecieverProxy::defaultTranslator(unsigned char* msgIn, size_t size, void* msgOut) {
	RecieverProxy::DefaultMessage* msg = static_cast<RecieverProxy::DefaultMessage*>(msgOut);
	msg->data = new unsigned char[size];
	memcpy(msg->data, msgIn, size);
	msg->length = size;
}

bool RecieverProxy::checkMessageQueueExist() {
	if (messageQueue == nullptr) return false;
	return true;
}