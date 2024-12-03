#include "LogEntry.h"

LogEntry::LogEntry(LogLevel level, std::string message, long long timestamp) {
	this->level = level;
	this->message = message;
	this->timestamp = timestamp;

}

long long LogEntry::getTimestamp() {
	return this->timestamp;
}
std::string LogEntry::getMessage() {
	return this->message;
}
