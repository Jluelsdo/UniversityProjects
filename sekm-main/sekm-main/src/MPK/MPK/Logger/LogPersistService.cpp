#include "LogPersistService.h"
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>

void LogPersistService::writeEntry(LogEntry logEntry) {

	ThreadMutexGuard threadGuard(*threadLock);
	{if (&threadGuard); };

	writeToFile(&logEntry);

	threadGuard.release();
}

void LogPersistService::writelogEntryMessage(LogEntryMessage logEntryMessage) {

	ThreadMutexGuard threadGuard(*threadLock);
	{if (&threadGuard); };

	writeToFile(&logEntryMessage);

	threadGuard.release();
}

void LogPersistService::setfilePath(std::string filePath) {
	this->filePath = filePath;
}
void LogPersistService::setfileName(std::string fileName) {
	this->fileName = fileName;
}
void LogPersistService::setlogLevel(LogLevel logLevel) {
	this->logLevel = logLevel;
}
void LogPersistService::setmaxBytes(int maxBytes) {
	this->maxbytes = maxBytes;
}

LogPersistService::LogPersistService(std::string filePath, std::string fileName) {
	this->filePath = filePath;
	this->fileName = fileName;

	threadLock = new ThreadMutex;

	file.open(fileName, std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
	file.flush();
	file.seekp(0, std::ios::end);
}
LogPersistService::LogPersistService() {
}
LogPersistService::~LogPersistService() {
	file.close();
}
void LogPersistService::writeToFile(LogEntry* logEntry) {

	std::string s = "{'timestamp': '" + std::to_string(logEntry->getTimestamp()) + "', ";
	s += "'log': '" + logEntry->getMessage() +"'}\n";

	if ((int)file.tellg() + (int)s.length()  > maxbytes) {
		file.seekp(0, std::ios::beg);
	}
	file.write(s.data(), s.size());
	file.flush();

}
void LogPersistService::writeToFile(LogEntryMessage* logEntryMessage) {
	
	if (!file.is_open()) {
		std::cout << "Error opening file: " + fileName << std::endl;
		return;
	}

	std::string s = "{'timestamp': '" + std::to_string(logEntryMessage->getTimestamp()) + "', ";
	s += "'isshorted': '" + std::to_string(logEntryMessage->isShorted()) + "', ";
	s += "'method': '" + logEntryMessage->getMethod() + "', ";
	s += "'message': '";

	std::string tail = "'}\n";

	if ((int)file.tellg() + ((int)s.length() + logEntryMessage->getSize() + tail.length()) > maxbytes) {

		file.seekp(0, std::ios::beg);
	}

	file.write(s.data(), s.size());
	file.write((const char*)logEntryMessage->getMessage(), logEntryMessage->getSize()-1);
	file.write(tail.data(), tail.size());

	file.flush();

}
