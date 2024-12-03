#include "Logger.h"
#include <time.h>
#include <ctime>
#include <chrono>


void Logger::setlogPersistSerivce(LogPersistService* logPersistSerivce) {
	this->logPersistSerivce = logPersistSerivce;
}

void Logger::setLoggerId(std::string id) {
	this->id = id;
}
void Logger::logMessage(std::string method, unsigned char* message, size_t size, bool shorted) {
	if (this->logLevel >= 2 && this->logMessageEnabled) {
		long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count();

		LogEntryMessage logEntryMessage = LogEntryMessage(method, message, size, shorted, timestamp);

		logPersistSerivce->writelogEntryMessage(logEntryMessage);
	}
}

void Logger::info(std::string message) {
	if (this->logLevel >= 2) {
		long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count();

		LogEntry logEntry = LogEntry(Info, message, timestamp);
		logPersistSerivce->writeEntry(logEntry);
	}
}
void Logger::setLogLevel(LogLevel logLevel) {
	this->logLevel = logLevel;
}

void Logger::warning(std::string message) {
	if (this->logLevel >= 1) {
		long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count();

		LogEntry logEntry = LogEntry(Warning, message, timestamp);
		logPersistSerivce->writeEntry(logEntry);
	}
}

void Logger::error(std::string message) {
	if (this->logLevel >= 0) {
		long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count();

		LogEntry logEntry = LogEntry(Error, message, timestamp);
		logPersistSerivce->writeEntry(logEntry);
	}
}



void Logger::debug(std::string message) {
	if (this->logLevel == 3) {
		long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count();

		printf("{'timestmap':'%lld', 'unit':'%s', 'log':'%s'}\n", timestamp, id.c_str(), message.c_str());

		LogEntry logEntry = LogEntry(Debug, message, timestamp);
		logPersistSerivce->writeEntry(logEntry);
	}
}
std::string Logger::getLoggerId() {
	return this->id;
}