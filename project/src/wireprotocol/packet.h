#ifndef PACKET_H__
#define PACKET_H__

#include <memory>
using std::shared_ptr;

#include "../database/database.h"

/* Abstract superclass for packages */

class Packet {
public: 
	void eat(const uint8_t &expects ){
        uint8_t next;
        (&this) >> next;
        if (next != expects){
            throw ProtocolViolationException();
        }
    }

};


class AnsPacket : public Packet{
public:
	virtual void process() const;
};

class ComPacket : public Packet {
public:
	virtual shared_ptr<AnsPacket> process(Database& db) const;
};


Connection& operator>>(Connection &inConn, uint32_t &t) {
	t = 0;
	uint8_t byte;
	for(int i = 0; i < 4; ++i) {
		in >> byte;
		t = t << 8;
		t |= byte;
	}
	return inConn;
}

Connection& operator<<(Connection &outConn, uint32_t &rhs) {
	int bitOffset = 24;
	for(int i = 0; i < 4; ++i) {
		uint8_t byte = (rhs.value >> bitOffset) & 0xFF;
		out << byte;
		bitOffset -= 8
	}
	return outConn;
}

Connection& operator>>(Connection &inConn, uint8_t &rhs) {
	rhs = inConn.read();
	return inConn;
}

Connection& operator<<(Connection &outConn, uint8_t &rhs) {
	outConn.write(rhs);
	return outConn;
}


#endif
