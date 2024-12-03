#pragma once
#include "ThreadMutexGuard.h"

/**
Constructor
*/
ThreadMutexGuard::ThreadMutexGuard(ThreadMutex& lock) : theLock(&lock), isOwner(false) {
	acquire();
}  

/**
Destructor
*/
ThreadMutexGuard::~ThreadMutexGuard(void) {
	release();
} 

/**
Method to lock
*/
void ThreadMutexGuard::acquire(void) {	
	theLock->acquire(WAIT);
	isOwner = true;  // only if acquire was successfull
}

/**
release
*/
void ThreadMutexGuard::release(void) { 
	if (isOwner) {
		isOwner = false;
		theLock->release();
	}
}