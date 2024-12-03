#include "SenderProxy.h"
#include "Channel.h"

SenderProxy::SenderProxy(Channel** channel) {
	this->channel = channel;
}

int SenderProxy::addMessage(unsigned char* message, size_t size) {
	// Check if there is a problem with the pointers
	if (channel == nullptr || *channel == nullptr) {
		return -10;
	}

	// Check if the channel is flaged for deletion
	if ((*channel)->getFlagDelete()) {
			return -11;
	}

	// Add message to channel
	return (*channel)->addMessage(message, size);
}
