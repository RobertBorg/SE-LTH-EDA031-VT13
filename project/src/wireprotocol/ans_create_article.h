#ifndef ANS_CREATE_ARTICLE_H__
#define ANS_CREATE_ARTICLE_H__


class AnsCreateArticlePacket : public AnsPacket{
public:
	void process(){
		
	}

	AnsCreateArticlePacket() = default;
	AnsCreateArticlePacket(bool success_): success(success_){}


private:
	bool success;
};


Connection& operator>>(Connection &in, AnsCreateArticlePacket &rhs) {
	in.eat(protocol::ANS_CREATE_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol:ANS_ACK:
			rhs.success = true;
			break;

		case protocol:ANS_NAK:
			in.eat(protocol::ERR_NG_DOES_NOT_EXIST);
			rhs.success = false;
			break;

		default:
			throw ProcotolViolationException();
			break;

	}
	in.eat(protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsCreateArticlePacket &rhs) {
	out << protocol::ANS_CREATE_ART;
	if (success){
		out << protocol:ANS_ACK;
	} else {
		out << protocol:ANS_NAK;
		out << protocol:ERR_NG_DOES_NOT_EXIST;
	}
	out << protocol::ANS_END;
	return out;
}

#ifndef
