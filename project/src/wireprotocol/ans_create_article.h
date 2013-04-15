#ifndef ANS_CREATE_ARTICLE_H__
#define ANS_CREATE_ARTICLE_H__

#include "packet.h"


class AnsCreateArticlePacket : public AnsPacket{
public:
	void process(){
		if (success){
			cout << "Creation was succesful." << endl;
		} else {
			cout << "Newsgroup was not found." << endl;
		}
	}

	AnsCreateArticlePacket() = default;
	AnsCreateArticlePacket(bool success_): success(success_){}


private:
	bool success;
};


Connection& operator>>(Connection &in, AnsCreateArticlePacket &rhs) {
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
			throw ProcotolViolationException();
			break;

	}
	Packet::eat(in, protocol::Protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsCreateArticlePacket &rhs) {
	out << protocol::Protocol::ANS_CREATE_ART;
	if (success){
		out << protocol::Protocol::ANS_ACK;
	} else {
		out << protocol::Protocol::ANS_NAK;
		out << protocol::Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	out << protocol::Protocol::ANS_END;
	return out;
}

#endif
