#include "MessageFactory.h"

Message* MessageFactory::createMessage(size_t slotLen) {
	return new Message(slotLen);
}
