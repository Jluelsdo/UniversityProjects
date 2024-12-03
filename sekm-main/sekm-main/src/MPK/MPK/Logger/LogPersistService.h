#include <string>
#include "LogEntry.h"
#include "LogLevel.h"
#include "../Channel/ThreadMutex.h"
#include "../Channel/ThreadMutexGuard.h"
#include "LogEntryMessage.h"
#include <fstream>

#ifndef LOGGER_LOGPERSISTSERVICE_H
#define LOGGER_LOGPERSISTSERVICE_H


class LogPersistService {

private:
	std::string filePath;
	std::string fileName;
	LogLevel logLevel;
	long offSet = 0;
	int maxbytes = 0;

	ThreadMutex *threadLock;
	std::fstream file;

	FILE* pFile;

public:
	LogPersistService(std::string filePath, std::string fileName);
	LogPersistService();
	~LogPersistService();
	void writelogEntryMessage(LogEntryMessage logEntryMessage);
	void setfilePath(std::string filePath);
	void setfileName(std::string fileName);
	void setlogLevel(LogLevel logLevel);
	void setmaxRowCount(int maxRowCount);
	void writeEntry(LogEntry logEntry);
	void writeToFile(LogEntryMessage* logEntryMessage);
	void writeToFile(LogEntry* logEntry);

	void setmaxBytes(int maxBytes);
};


#endif
