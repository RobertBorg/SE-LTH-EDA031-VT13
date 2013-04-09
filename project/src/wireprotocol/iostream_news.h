#ifndef NEWSSTREAM_H__
#define NEWSSTREAM_H__

#include <iostream>

class iostream_news : public iostream {
public:
	void eat(const uint8_t &expects){
		uint8_t next;
		&this << next;
		if (next != expects){
			throw ProtocolViolationException();
		}
	}
};

#endif /* end of include guard: NEWSSTREAM_H__ */
