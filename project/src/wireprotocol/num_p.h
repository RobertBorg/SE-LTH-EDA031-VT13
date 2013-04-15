#ifndef NUM_P_H__
#define NUM_P_H__

#include <string>
#include <cstdint>
#include "../../lib/clientserver/protocol.h"

struct num_p : public Packet{
	num_p() = default;
	num_p(size_t size) : value(size) {}
	uint32_t value;
	operator uint32_t() const {
		return value;
	}
};


Connection& operator>>(Connection &in, num_p &rhs) {
	Packet::eat(in, protocol::Protocol::PAR_NUM);
	in >> rhs.value;
	return in;
}

Connection& operator<<(Connection &out, num_p &rhs) {
	out << protocol::Protocol::PAR_NUM;
	out << rhs.value;
	return out;
}

#endif /* end of include guard: NUM_P_H__ */
