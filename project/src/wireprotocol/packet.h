#ifndef PACKET_H__
#define PACKET_H__

/* Abstract superclass for packages */

class Packet {
public:
	void eat(const uint8_t &expects){
		uint8_t next;
		&this << next;
		if (next != expects){
			throw ProtocolViolationException();
		}
	}
};


class ComPacket : public Packet {
public:
	virtual shared_ptr<AnsPacket> process(Database *db) const;


};

class AnsPacket : public Packet{
public:
	virtual void process() const;


};


#endif