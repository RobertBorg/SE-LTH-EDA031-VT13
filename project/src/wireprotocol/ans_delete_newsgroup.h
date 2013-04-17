#ifndef ANS_DELETE_NEWSGROUP_H__
#define ANS_DELETE_NEWSGROUP_H__

#include "packet.h"

template <typename istream, typename ostream>
class AnsDeleteNewsgroupPacket : public AnsPacket<istream, ostream> {
friend istream& operator>>(istream &in, AnsDeleteNewsgroupPacket<istream, ostream> &rhs){
	Packet::eat(in, protocol::Protocol::ANS_DELETE_NG);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol::Protocol::ANS_ACK:
			rhs.success = true;
			break;

		case protocol::Protocol::ANS_NAK:
			Packet::eat(in, protocol::Protocol::ERR_NG_DOES_NOT_EXIST);
			rhs.success = false;
			break;

		default:
			throw SeralizationViolationException();
			break;

	}
	Packet::eat(in, protocol::Protocol::ANS_END);
	return in;
}
friend ostream& operator<<(ostream &out, AnsDeleteNewsgroupPacket<istream, ostream> &rhs){
	out << protocol::Protocol::ANS_DELETE_NG;
	if (rhs.success){
		out << protocol::Protocol::ANS_ACK;
	} else {
		out << protocol::Protocol::ANS_NAK;
		out << protocol::Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	out << protocol::Protocol::ANS_END;
	return out;
}
public:
	virtual void process() const{
		if (this->success){
			cout << "Newsgroup successfully deleted." << endl;
		} else {
			cout << "Newgroup was not found." << endl;
		}
	}
	AnsDeleteNewsgroupPacket() = default;
	AnsDeleteNewsgroupPacket(bool success_): success(success_){}

	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	bool success;
};

#endif
