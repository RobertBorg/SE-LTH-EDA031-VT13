#ifndef ANS_CREATE_ARTICLE_H__
#define ANS_CREATE_ARTICLE_H__

#include "packet.h"
#include "../../lib/clientserver/protocol.h"

template <typename istream, typename ostream>
class AnsCreateArticlePacket : public AnsPacket<istream, ostream>{
friend istream& operator>>(istream &in, AnsCreateArticlePacket &rhs){
	Packet::eat(in, protocol::Protocol::ANS_CREATE_ART);
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
friend ostream& operator<<(ostream &out, AnsCreateArticlePacket &rhs){
	out << protocol::Protocol::ANS_CREATE_ART;
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
	AnsCreateArticlePacket() = default;
	AnsCreateArticlePacket(bool success_): success(success_){}

	virtual void process() const{
		if (this->success){
			cout << "Creation was succesful." << endl;
		} else {
			cout << "Newsgroup was not found." << endl;
		}
	}

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
