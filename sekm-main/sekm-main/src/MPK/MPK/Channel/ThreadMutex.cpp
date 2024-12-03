#pragma once
#include "ThreadMutex.h"

ThreadMutex::ThreadMutex(void) {
	isInitialized = InitializeCriticalSectionAndSpinCount(&theMutex, 0x80000400);
}
ThreadMutex::~ThreadMutex(void) {
	DeleteCriticalSection(&theMutex);
}
void ThreadMutex::acquire(bool waitOnEntry) {
	if (waitOnEntry == WAIT) {
		EnterCriticalSection(&theMutex);
	}
	else { //NOWAIT, acquire returns without blocking if theMutex is not available
		TryEnterCriticalSection(&theMutex);
	}
}
void ThreadMutex::release(void) {
	LeaveCriticalSection(&theMutex);
}
