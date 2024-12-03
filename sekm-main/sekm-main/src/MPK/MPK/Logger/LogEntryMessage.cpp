#include "LogEntryMessage.h"

LogEntryMessage::LogEntryMessage(std::string method, unsigned char* message, size_t size, bool shorted, long long timestmap) {
	this->method = method;
	this->message = message;
	this->timestamp = timestmap;
	this->shorted = shorted;
	this->size = size;
}

long long LogEntryMessage::getTimestamp() {
	return timestamp;
}
unsigned char* LogEntryMessage::getMessage() {
	return message;
}
std::string LogEntryMessage::getMethod() {
	return method;
}
bool LogEntryMessage::isShorted() {
	return shorted;
}
size_t LogEntryMessage::getSize() {
	return size;
}


