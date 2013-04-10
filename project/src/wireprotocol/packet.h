#ifndef PACKET_H__
#define PACKET_H__

/* Abstract superclass for packages */


class ComPacket {
public:
	virtual shared_ptr<AnsPacket> process(Database *db) const;


};

class AnsPacket {
public:
	virtual void process() const;


};


#endif