#ifndef ANS_DELETE_ARTICLE_H__
#define ANS_DELETE_ARTICLE_H__


class AnsDeleteArticlePacket : public AnsPacket{
public:
	void process(){
		
	}
	AnsDeleteArticlePacket(bool success_, bool ngNotFound_, bool artNotFound_) 
		: success(success_), ngNotFound(ngNotFound_), artNotFound(artNotFound_){}


private:
	bool success, ngNotFound, artNotFound;
};


istream_news& operator>>(istream_news &in, AnsDeleteArticlePacket &rhs) {
	in.eat(Protocol::ANS_CREATE_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case Protocol::ANS_ACK:
			rhs.success = true;
			break;

		case Protocol:ANS_NAK:
			uint8_t errorMsg;
			in >> errorMsg;
			switch(errorMsg){
				case Protocol::ERR_NG_DOES_NOT_EXIST:
					rhs.ngNotFound = true;
					break;
				case Protocol::ERR_ART_DOES_NOT_EXIST:
					rhs.artNotFound = true;
					break
				default:
					throw ProcotolViolationException();
			}
			rhs.success = false;
			break;

		default:
			throw ProcotolViolationException();
			break;

	}
	in.eat(Protocol::ANS_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, AnsDeleteArticlePacket &rhs) {
	out << Protocol::ANS_CREATE_ART;
	if (rhs.success){
		out << Protocol:ANS_ACK;
	} else {
		out << Protocol:ANS_NAK;
		if (rhs.ngNotFound){
			out << Protocol:ERR_NG_DOES_NOT_EXIST;
		} else {
			out << Protocol:ERR_ART_DOES_NOT_EXIST;
		}
	}
	out << Protocol::ANS_END;
	return out;
}

#ifndef
