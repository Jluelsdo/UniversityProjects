#pragma once

#define WAIT TRUE
#define NOWAIT FALSE

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdio.h>


class ThreadMutex
{
public:
	ThreadMutex(void);  // Constructor
	~ThreadMutex(void);  // Destructor
	void acquire(bool waitOnEntry); // Lock
	void release(void); // release
private:
	CRITICAL_SECTION theMutex; // WIN32 Mutex mechanism
	bool isInitialized;
	ThreadMutex(const ThreadMutex&); // safty for copies ThreadMutex
	void operator= (const ThreadMutex&); // safety for assignments of ThreadMutex
};
