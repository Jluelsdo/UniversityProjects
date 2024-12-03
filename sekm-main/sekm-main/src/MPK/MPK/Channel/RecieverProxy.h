#include <functional>
#include "MessageQueue.h"
#include "Channel.h"
#include "ChannelRegistry.h"
#include <thread>

#ifndef RECIEVERPROXY_H
#define RECIEVERPROXY_H


class RecieverProxy {

public:
	typedef std::function<void(unsigned char*, size_t, void*)> callback_t;

	struct DefaultMessage {
		size_t length = 0;
		unsigned char* data = nullptr;
	};

private:
	long uid;
	size_t recieverSlotLen;
	Channel** channel;
	MessageQueue* messageQueue;
	callback_t callbackTranslator;
	int cVersion;

	MessageQueue* getMessageQueueFromChannel();

	/**
	* Check if the channel is marked for deletion and empty
	*/
	void channelManagment();
	static void defaultTranslator(unsigned char* msgIn, size_t size, void* msgOut);
public:
	RecieverProxy(Channel** channel, size_t recieverSlotLen);

	void setCallbackTranslator(callback_t callbackTranslator) { this->callbackTranslator = callbackTranslator;  }

	/**
	* Read next message from messageQueue and translate
	* Returns:
	* -1 then there is no channel
	* -2 then there is no messageQueue
	* -3 then there is no message
	*/
	int readMessage(void* message);

	/**
	* Wait for next message from messageQueue and translate
	* Returns:
	* -1 then there is no channel
	* -2 then there is no messageQueue
	* -10 for timeout
	*/
	int readMessageWait(void* message, long long timeout);

	/**
	 * Calls deleteChannel from ChannelRegistery
	 */
	void deleteChannel();

	bool checkMessageQueueExist();

};

#endif
