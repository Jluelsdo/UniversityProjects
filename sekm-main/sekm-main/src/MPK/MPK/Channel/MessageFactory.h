#include "Message.h"
#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

class MessageFactory {


public:
	/**
	* Creates an object of the class Message
	*/
	Message* createMessage(size_t slotLen);
};

#endif
