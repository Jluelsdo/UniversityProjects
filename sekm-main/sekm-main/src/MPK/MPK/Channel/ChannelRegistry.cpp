#include "ChannelRegistry.h"

ChannelRegistry* ChannelRegistry::instance = nullptr;

ChannelRegistry& ChannelRegistry::getInstance() {
	if (!instance){
		instance = new ChannelRegistry();
	}
	return *instance;
}
ChannelRegistry::ChannelRegistry() {
	threadLockAddUid = new ThreadMutex;
	threadLockReinit = new ThreadMutex;
	threadLockAddChannel = new ThreadMutex;
	threadLockdeleteChannel = new ThreadMutex;
}
ChannelRegistry::~ChannelRegistry() {
	delete threadLockAddUid;
	delete threadLockReinit;
	delete threadLockAddChannel;
	delete threadLockdeleteChannel;
}

Channel** ChannelRegistry::getChannelByID(long kid) {
	for (auto channel : channels) {
		int kid = (*channel)->getKID();
		if (kid == kid) {
			return channel;
		}
	}
	return nullptr;
}

void ChannelRegistry::reinitAllChannel() {
	for (auto channel : channels) {
		InitUnit::getInstance().reinitChannelById((*channel)->getKID());
	}
}

void ChannelRegistry::deleteChannel(long kid) {

	ThreadMutexGuard threadGuard(*threadLockReinit);
	{if (&threadGuard); };

	Channel** channelReferenz = getChannelByID(kid);
	if (channelReferenz != nullptr){
		channels.remove_if([kid](auto& element) {return (*element)->getKID() == kid; });
		delete(*channelReferenz);
		*channelReferenz = nullptr;
	}
	threadGuard.release();
}

int ChannelRegistry::reinitChannel(ChannelConfig channelConfig) {
	
	ThreadMutexGuard threadGuard(*threadLockReinit);
	{if (&threadGuard); };

	Channel** channel = getChannelByID(channelConfig.kid);
	if (channel == nullptr || (*channel) == nullptr) {
		threadGuard.release();
		return -1;
	}

	//Add new Channel
	Channel** newchannel = addChannel(channelConfig.kid, channelConfig.flagDynamicQueue, channelConfig.flagMultiReciever);
	(*newchannel)->setFlagDelete(channelConfig.flagDelete);
	(*newchannel)->setMaxChannelSlotLen(channelConfig.slotLength);
	(*newchannel)->setCVersion(++channelConfig.cVersion);
	
	// Create one MessageQueue for every reciever
	for (auto reciever : channelConfig.receivers) {
		(*newchannel)->createMessageQueue(channelConfig.slotLength, reciever);
	}

	Channel* oldChannel = *channel;
	//Update Proxy References
	*channel = *newchannel;
	//Remove old Channel without any existing references
	delete(oldChannel);

	threadGuard.release();

	return 0;
}

 
Channel** ChannelRegistry::addChannel(long kid, bool flagDynamicQueue, bool flagMultiReciever) {

	ThreadMutexGuard threadGuard(*threadLockAddUid);
	{if (&threadGuard); };

	ChannelFactory factory;
	Channel** newChannel = new Channel*;
	*newChannel = factory.createChannel(kid, flagDynamicQueue, flagMultiReciever);
	channels.push_back(newChannel);

	threadGuard.release();

	return newChannel;
}

long ChannelRegistry::createUID() {

	ThreadMutexGuard threadGuard(*threadLockAddUid);
	{if (&threadGuard); };

	long uid = uid_count;
	uid_count++;

	threadGuard.release();

	return uid;
}
