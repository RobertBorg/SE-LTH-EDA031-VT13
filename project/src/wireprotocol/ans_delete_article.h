#ifndef ANS_DELETE_ARTICLE_H__
#define ANS_DELETE_ARTICLE_H__


class AnsDeleteArticlePacket : public AnsPacket{
public:
	void process(){
		if (success){
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

	static &AnsDeleteArticlePacket createSuccesful(){
		return new AnsDeleteArticlePacket(true, false, false);
	}
	static &AnsDeleteArticlePacket createNGNotFound(){
		return new AnsDeleteArticlePacket(false, true, false);
	}
	static &AnsDeleteArticlePacket createArtNotFound(){
		return new AnsDeleteArticlePacket(false, false, true);
	}


private:
	bool success, ngNotFound, artNotFound;
};


Connection& operator>>(Connection &in, AnsDeleteArticlePacket &rhs) {
	Packet::eat(in, protocol::ANS_CREATE_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol::ANS_ACK:
			rhs.success = true;
			break;

		case protocol:ANS_NAK:
			uint8_t errorMsg;
			in >> errorMsg;
			switch(errorMsg){
				case protocol::ERR_NG_DOES_NOT_EXIST:
					rhs.ngNotFound = true;
					break;
				case protocol::ERR_ART_DOES_NOT_EXIST:
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
	Packet::eat(in, protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsDeleteArticlePacket &rhs) {
	out << protocol::ANS_CREATE_ART;
	if (rhs.success){
		out << protocol:ANS_ACK;
	} else {
		out << protocol:ANS_NAK;
		if (rhs.ngNotFound){
			out << protocol:ERR_NG_DOES_NOT_EXIST;
		} else {
			out << protocol:ERR_ART_DOES_NOT_EXIST;
		}
	}
	out << protocol::ANS_END;
	return out;
}

#ifndef
