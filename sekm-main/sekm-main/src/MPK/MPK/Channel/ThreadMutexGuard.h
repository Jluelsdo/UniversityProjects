#pragma once
#include "ThreadMutex.h"
#define UNUSED_ARG(arg) {if (&arg) /* do nothing */ ; }

class ThreadMutexGuard 
{
public:
	ThreadMutexGuard(ThreadMutex &lock);
	~ThreadMutexGuard(void);
	void release(void);
private:
	void acquire(void);
	ThreadMutex* theLock;  // Pointer, points on the lock
	bool isOwner;		// Mark if lock is still acquired
	ThreadMutexGuard(const ThreadMutexGuard&); // safty for copies
	void operator= (const ThreadMutexGuard&); // Safty for assignment
};
