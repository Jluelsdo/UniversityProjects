#include "ConnectUnit.h"
#include "../Initialization/InitUnit.h"



RecieverProxy* ConnectUnit::connectReciever(long kid, size_t recieverSlotLen, size_t maxChannelSlotLen, bool flagDynamicQueue, bool flagMultiReciever, bool flagInitialize) {
	// get Channel
	Channel** channel = ChannelRegistry::getInstance().getChannelByID(kid);
	// Ensure that if a channel exists it has the correct setup
	// Channel exists
	if (channel != nullptr) {
		// Channel is flagged for delition
		if ((*channel)->getFlagDelete()) {
			return nullptr;
		}

		// Requesting Channel Setup and existing Channel Setup
		if ((*channel)->getMaxChannelSlotLen() != maxChannelSlotLen
			&& maxChannelSlotLen != 0) {
			return nullptr;
		}
		if ((*channel)->getFlagMultiReciever() != flagMultiReciever) {
			return nullptr;
		}
		if ((*channel)->getFlagDynamicQueue() != flagDynamicQueue) {
			return nullptr;
		}
		if ((*channel)->getMaxChannelSlotLen() < recieverSlotLen) {
			return nullptr;
		}
	}
	// Channel doesn't exist
	else {
		// Channel should not be initialized
		if (!flagInitialize) {
			InitUnit::getInstance().getLogger()->info("Channel is not set for initialization");
			return nullptr;
		}
		// Checked if the slot length is longer as allowed
		if (!flagDynamicQueue
			&& (maxChannelSlotLen > StaticQueue::absoluteMaxSlotLen
				|| recieverSlotLen > StaticQueue::absoluteMaxSlotLen)) {
			InitUnit::getInstance().getLogger()->info("absoluteMaxSlotLen exceeded");
			return nullptr;
		}
		if (maxChannelSlotLen != 0 && maxChannelSlotLen < recieverSlotLen) {
			InitUnit::getInstance().getLogger()->info("maxChannelSlotLen exceeded");
			return nullptr;
		}

		// Create a new channel
		channel = InitUnit::getInstance().initChannel(kid, flagDynamicQueue, flagMultiReciever);
		
		if (maxChannelSlotLen != 0) (*channel)->setMaxChannelSlotLen(maxChannelSlotLen);
	}
	ProxyFactory proxyFactory = ProxyFactory();
	RecieverProxy* recieverProxy = proxyFactory.createRecieverProxy(channel, recieverSlotLen);
	
	if (!recieverProxy->checkMessageQueueExist()) {
		InitUnit::getInstance().getLogger()->info("checkMessageQueueExist failed");
		return nullptr;
	}
	return recieverProxy;
}

RecieverProxy* ConnectUnit::connectReciever(long kid, size_t recieverSlotLen, bool flagInitialize) {
	return connectReciever(kid, recieverSlotLen, 0, false, false, flagInitialize);
}

SenderProxy* ConnectUnit::connectSender(long kid, size_t maxChannelSlotLen, bool flagDynamicQueue, bool flagMultiReciever, bool flagInitialize) {
	// get or create Channel
	Channel** channel = ChannelRegistry::getInstance().getChannelByID(kid);
	if (channel != nullptr) {
		// Channel is flagged for delition
		if ((*channel)->getFlagDelete()) {
			InitUnit::getInstance().getLogger()->info("Channel flagged for deletion");
			return nullptr;
		}
		// Channel Slot length doesnt fit
		if ((*channel)->getMaxChannelSlotLen() != maxChannelSlotLen
			&& maxChannelSlotLen != 0) {
			InitUnit::getInstance().getLogger()->info("Channel Slot length doesnt fit");
			return nullptr;
		}
		// Requesting Channel Setup and existing Channel Setup
		if ((*channel)->getFlagMultiReciever() != flagMultiReciever) {
			InitUnit::getInstance().getLogger()->info("flagMultiReciever does not match");
			return nullptr;
		}
		if ((*channel)->getFlagDynamicQueue() != flagDynamicQueue) {
			InitUnit::getInstance().getLogger()->info("flagDynamicQueue does not match");
			return nullptr;
		}
	}
	else {
		if (!flagInitialize) {
			InitUnit::getInstance().getLogger()->info("Channel not flagged for initialization");
			return nullptr;
		}
		// Checked if the slot length is longer as allowed
		if (!flagDynamicQueue && maxChannelSlotLen > StaticQueue::absoluteMaxSlotLen) return nullptr;
		
		// Creat a new channel
		channel = InitUnit::getInstance().initChannel(kid, flagDynamicQueue, flagMultiReciever);
		if (maxChannelSlotLen != 0) (*channel)->setMaxChannelSlotLen(maxChannelSlotLen);
	}

	// Create a new Proxy
	ProxyFactory proxyFactory = ProxyFactory();
	SenderProxy* senderProxy = proxyFactory.createSenderProxy(channel);

	return senderProxy;
}

SenderProxy* ConnectUnit::connectSender(long kid, bool flagInitialize) {
	return connectSender(kid, 0, false, false, flagInitialize);
}

void ConnectUnit::reinitChannel(int kid) {
	InitUnit::getInstance().reinitChannelById(kid);
}

void reinitAllChannel() {
	InitUnit::getInstance().reinitAllChannel();
}