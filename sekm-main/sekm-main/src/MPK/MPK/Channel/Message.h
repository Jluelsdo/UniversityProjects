#include <stdlib.h>
#include <cstring>
#ifndef MESSAGE_H
#define MESSAGE_H


class Message {

private:
	/**
	 * µ-Sekunden die vergangen sind nach dem 1.1.1970
	 */
	long long timestamp = 0;
	unsigned char* data;
	bool cutState = false;
	size_t size = 0;

	friend class StaticQueue;
	friend class DynamicQueue;

public:
	size_t getSize() { return size; }
	bool getCutState() { return cutState; }
	unsigned char* getData() { return data; }
	long long getTimestamp() { return timestamp;}

	Message(size_t slotLen) {
		data = (unsigned char*)malloc(slotLen);
	}

	~Message() {
		free(data);
	}

	static int copyMessage(Message* dst, Message* src) {
		// Copy meta data
		dst->cutState = src->cutState;
		dst->timestamp = src->timestamp;
		dst->size = src->size;
		
		// Check that the data memory is initialized
		if (src->data == nullptr || dst->data == nullptr) return -1;
		
		// Copy data
		memcpy(dst->data, src->data, src->size);
		return 0;
	}
};

#endif
