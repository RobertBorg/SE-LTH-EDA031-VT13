#ifndef PACKET_H__
#define PACKET_H__

#include <memory>
using std::shared_ptr;

#include "../database/database.h"

#include "../../lib/clientserver/connection.h"
using client_server::Connection;
#include "../../lib/clientserver/protocol.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;


struct SeralizationViolationException {
	uint8_t expected;
	uint8_t actual;
};

template <typename istream>
istream& operator>>(istream &in, uint8_t &rhs) {
	rhs = in.get();
	return in;
}

template <>
Connection& operator>><Connection>(Connection &in, uint8_t &rhs) {
	rhs = in.read();
	return in;
}

template <typename istream>
istream& operator>>(istream &in, char &rhs) {
	rhs = in.get();
	return in;
}

template <>
Connection& operator>><Connection>(Connection &in, char &rhs) {
	rhs = in.read();
	return in;
}


template <typename ostream>
ostream& operator<<(ostream &out, const char &rhs) {
	out.put(rhs);
	return out;
}

template <>
Connection& operator<<<Connection>(Connection &out, const char &rhs) {
	out.write(rhs);
	return out;
}

template <typename ostream>
ostream& operator<<(ostream &out, const uint8_t &rhs) {
	out.put(rhs);
	return out;
}

template <>
Connection& operator<<<Connection>(Connection &out, const uint8_t &rhs) {
	out.write(rhs);
	return out;
}

template <typename ostream>
ostream& operator<<(ostream &out, const protocol::Protocol::proto &rhs) {
	uint8_t temp = rhs;
	out << temp;
	return out;
}

template <typename istream>
istream& operator>>(istream &in, protocol::Protocol::proto &rhs) {
	uint8_t temp;
	in >> temp;
	rhs = static_cast<protocol::Protocol::proto>(temp);
	return in;
}


template <typename istream>
istream& operator>>(istream &in, uint32_t &t) {
	t = 0;
	uint8_t byte;
	for(int i = 0; i < 4; ++i) {
		in >> byte;
		t = t << 8;
		t |= byte;
	}
	return in;
}

template <typename ostream>
ostream& operator<<(ostream &out, uint32_t rhs) {
	int bitOffset = 24;
	for(int i = 0; i < 4; ++i) {
		uint8_t byte = (rhs >> bitOffset) & 0xFF;
		out << byte;
		bitOffset -= 8;
	}
	return out;
}

template <typename ostream>
ostream& operator<<(ostream &out, int &rhs) {
	out << static_cast<uint32_t>(rhs);
	return out;
}



class Packet {
public: 
	template <typename istream>
	static void eat(istream &in, const uint8_t &expects ){
        uint8_t next;
        in >> next;
        if (next != expects){
        	SeralizationViolationException pe;
        	pe.expected = expects;
        	pe.actual = next;
        	
            throw pe;
        }
    }


};

template <typename istream = Connection, typename ostream = Connection>
class AnsPacket : public Packet{
public:
	virtual void process() const {
	}

	virtual void write(ostream &out) {
		cerr << "write not overloaded" << endl;
	}

	virtual void read(istream &in) {
		cerr << "read not overloaded" << endl;
	}
};

template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComPacket : public Packet {
public:
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const {
		return nullptr;
	}

	virtual void write(ostream &out) {
		cerr << "write not overloaded" << endl;
	}

	virtual void read(istream &in) {
		cerr << "read not overloaded" << endl;
	}
};

#endif
