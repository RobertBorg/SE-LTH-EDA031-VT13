#ifndef NUM_P_H__
#define NUM_P_H__

#include <string>
#include <cstdint>

struct num_p {
	num_p() = default;
	num_p(size_t &size) : value(size) {}
	uint32_t value;
};

istream& operator>>(istream &in, num_p &rhs) {
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

ostream& operator<<(ostream &out, num_p &rhs) {
	int bitOffset = 24;
	for(int i = 0; i < 4; ++i) {
		char byte = (rhs.value >> bitOffset) & 0xFF;
		out << byte;
		bitOffset -= 8
	}
	return out;
}

#endif /* end of include guard: NUM_P_H__ */