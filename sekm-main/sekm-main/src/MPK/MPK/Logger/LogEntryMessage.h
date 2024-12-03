#include <string>

#ifndef LOGGER_LOGENTRYMESSAGE_H
#define LOGGER_LOGENTRYMESSAGE_H

class LogEntryMessage {

private:
	std::string method;
	unsigned char* message;
	size_t size;
	bool shorted;
	long long timestamp;

public:
	LogEntryMessage(std::string method, unsigned char* message, size_t size, bool shorted, long long timestmap);
	long long getTimestamp();
	unsigned char* getMessage();
	bool isShorted();
	size_t getSize();
	std::string getMethod();
};


#endif
