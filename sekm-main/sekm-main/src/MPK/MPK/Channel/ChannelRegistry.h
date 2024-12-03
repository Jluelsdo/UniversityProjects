#pragma once

#include <list>
#include <vector>

#include "Channel.h"
#include "SenderProxy.h"
#include "ChannelFactory.h"
#include "ThreadMutexGuard.h"
#include "../Initialization/ChannelConfig.h"
#include "../Initialization/InitUnit.h"
#include "AbstractMessageQueueFactory.h"

#ifndef CHANNELREGISTRY_H
#define CHANNELREGISTRY_H

class ChannelRegistry {
	
public:
	
private:
	static ChannelRegistry* instance;

	ThreadMutex* threadLockAddUid;
	ThreadMutex* threadLockReinit;
	ThreadMutex* threadLockAddChannel;
	ThreadMutex* threadLockdeleteChannel;

	std::list<Channel**> channels;

	long uid_count = 0;

protected:
	ChannelRegistry();
	~ChannelRegistry();
	ChannelRegistry(ChannelRegistry const&){}
	void operator=(ChannelRegistry const&){}


public:
	static ChannelRegistry& getInstance();

	/**
	 * get channel object reference by kid
	 */
	Channel** getChannelByID(long kid);

	/**
	 * Returns Channel
	 */
	Channel** addChannel(long kid, bool flagDynamicQueue, bool flagMultiReciever);

	/**
	* Delete Channel
	*/
	void deleteChannel(long kid);

	/**
	* Forced a channel deletion and 
	* created a new one with given config
	*/
	int reinitChannel(ChannelConfig channelConfig);

	/**
	* Reinit all Channels
	*/

	void ChannelRegistry::reinitAllChannel();

	/**
	* Returns a new User ID
	*/
	long createUID();
};

#endif
