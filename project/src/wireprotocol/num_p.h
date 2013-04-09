#ifndef NUM_P_H__
#define NUM_P_H__

#include "iostream_news.h"

#include <string>
#include <cstdint>
#include ".../../lib/clientserver/protocol.h"

struct num_p {
	num_p() = default;
	num_p(size_t &size) : value(size) {}
	uint32_t value;

private:
	void extractN(istream_news &in, uint32_t &t) {
		t = 0;
		for(int i = 0; i < 4; ++i) {
		in >> byte;
		t = t << 8;
		t |= byte;
	}
	}
};

operator unsigned int() const {
	return value;
}

istream_news& operator>>(istream_news &in, num_p &rhs) {
	in.eat(protocol::PAR_NUM)
	uint32_t t = 0;
	char byte = 0;

	for(int i = 0; i < 4; ++i) {
		in >> byte;
		t = t << 8;
		t |= byte;
	}

	rhs.value = t;
	return in;
}

iostream_news& operator<<(iostream_news &out, num_p &rhs) {
	int bitOffset = 24;
	for(int i = 0; i < 4; ++i) {
		char byte = (rhs.value >> bitOffset) & 0xFF;
		out << byte;
		bitOffset -= 8
	}
	return out;
}

#endif /* end of include guard: NUM_P_H__ */