#ifndef ANS_DELETE_ARTICLE_H__
#define ANS_DELETE_ARTICLE_H__

#include "packet.h"

template <typename istream, typename ostream>
class AnsDeleteArticlePacket : public AnsPacket<istream, ostream>{
friend istream& operator>>(istream &in, AnsDeleteArticlePacket<istream, ostream> &rhs){
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
					throw SeralizationViolationException();
			}
			rhs.success = false;
			break;

		default:
			throw SeralizationViolationException();
			break;

	}
	Packet::eat(in, protocol::Protocol::ANS_END);
	return in;
}
friend ostream& operator<<(ostream &out, AnsDeleteArticlePacket<istream, ostream> &rhs){
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

	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	bool success, ngNotFound, artNotFound;
};


#endif
