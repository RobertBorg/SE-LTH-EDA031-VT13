#ifndef ANS_DELETE_ARTICLE_H__
#define ANS_DELETE_ARTICLE_H__

#include "packet.h"

class AnsDeleteArticlePacket : public AnsPacket{
friend Connection& operator>>(Connection &in, AnsDeleteArticlePacket &rhs);
friend Connection& operator<<(Connection &out, AnsDeleteArticlePacket &rhs);
public:
	virtual void process() const{
		if (this->success){
			cout << "Article successfully deleted." << endl;
		} else if (ngNotFound){
			cout << "Newsgroup not found." << endl;
		} else if (artNotFound){
			cout << "Article not found." << endl;
		}
	}
	AnsDeleteArticlePacket() = default;
	AnsDeleteArticlePacket(bool success_, bool ngNotFound_, bool artNotFound_) 
		: success(success_), ngNotFound(ngNotFound_), artNotFound(artNotFound_){}

	static shared_ptr<AnsDeleteArticlePacket> createSuccessful(){
		return shared_ptr<AnsDeleteArticlePacket>(new AnsDeleteArticlePacket(true, false, false));
	}
	static shared_ptr<AnsDeleteArticlePacket> createNGNotFound(){
		return shared_ptr<AnsDeleteArticlePacket>(new AnsDeleteArticlePacket(false, true, false));
	}
	static shared_ptr<AnsDeleteArticlePacket> createArtNotFound(){
		return shared_ptr<AnsDeleteArticlePacket>(new AnsDeleteArticlePacket(false, false, true));
	}


private:
	bool success, ngNotFound, artNotFound;
};


Connection& operator>>(Connection &in, AnsDeleteArticlePacket &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_CREATE_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol::Protocol::ANS_ACK:
			rhs.success = true;
			break;

		case protocol::Protocol::ANS_NAK:
			uint8_t errorMsg;
			in >> errorMsg;
			switch(errorMsg){
				case protocol::Protocol::ERR_NG_DOES_NOT_EXIST:
					rhs.ngNotFound = true;
					break;
				case protocol::Protocol::ERR_ART_DOES_NOT_EXIST:
					rhs.artNotFound = true;
					break;
				default:
					throw ProtocolViolationException();
			}
			rhs.success = false;
			break;

		default:
			throw ProtocolViolationException();
			break;

	}
	Packet::eat(in, protocol::Protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsDeleteArticlePacket &rhs) {
	out << protocol::Protocol::ANS_CREATE_ART;
	if (rhs.success){
		out << protocol::Protocol::ANS_ACK;
	} else {
		out << protocol::Protocol::ANS_NAK;
		if (rhs.ngNotFound){
			out << protocol::Protocol::ERR_NG_DOES_NOT_EXIST;
		} else {
			out << protocol::Protocol::ERR_ART_DOES_NOT_EXIST;
		}
	}
	out << protocol::Protocol::ANS_END;
	return out;
}

#endif
