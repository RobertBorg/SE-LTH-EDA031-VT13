#ifndef PACKET_H__
#define PACKET_H__

#include <memory>
using std::shared_ptr;

#include "../database/database.h"

#include "../../lib/clientserver/connection.h"
using client_server::Connection;


struct ProtocolViolationException{};

Connection& operator>>(Connection &in, uint8_t &rhs) {
	rhs = in.read();
	return in;
}

Connection& operator>>(Connection &in, char &rhs) {
	rhs = in.read();
	return in;
}

Connection& operator<<(Connection &out, uint8_t &rhs) {
	out.write(rhs);
	return out;
}

Connection& operator>>(Connection &in, uint32_t &t) {
	t = 0;
	uint8_t byte;
	for(int i = 0; i < 4; ++i) {
		in >> byte;
		t = t << 8;
		t |= byte;
	}
	return in;
}

Connection& operator<<(Connection &out, uint32_t rhs) {
	int bitOffset = 24;
	for(int i = 0; i < 4; ++i) {
		uint8_t byte = (rhs >> bitOffset) & 0xFF;
		out << byte;
		bitOffset -= 8;
	}
	return out;
}

Connection& operator<<(Connection &out, int &rhs) {
	out << static_cast<uint32_t>(rhs);
	return out;
}


class Packet {
public: 
	static void eat(Connection &in, const uint8_t &expects ){
        uint8_t next;
        in >> next;
        if (next != expects){
            throw ProtocolViolationException();
        }
    }


};


class AnsPacket : public Packet{
public:
	virtual void process() const;
};

template <typename Database>
class ComPacket : public Packet {
public:
	virtual shared_ptr<AnsPacket> process(Database& db) const;
};

template<typename Packet>
Connection &operator<<(Connection &out, Packet &p) {
	out << p;
	return out;
}

template<typename Packet>
Connection &operator>>(Connection &in, Packet &p) {
	in >> p;
	return in;
}

#endif
