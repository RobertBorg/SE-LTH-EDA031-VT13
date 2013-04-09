#ifndef ANS_CREATE_ARTICLE_H__
#define ANS_CREATE_ARTICLE_H__


class AnsCreateArticle : public AnsPackage{
public:
	void process(){
		
	}
	AnsCreateArticle(bool success_): success(success_){}


private:
	bool success;
};


istream_news& operator>>(istream_news &in, AnsCreateArticle &rhs) {
	in.eat(Protocol::ANS_CREATE_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case Protocol:ANS_ACK:
			rhs.success = true;
			break;

		case Protocol:ANS_NAK:
			in.eat(Protocol::ERR_NG_DOES_NOT_EXIST);
			rhs.success = false;
			break;

		default:
			throw ProcotolViolationException();
			break;

	}
	in.eat(Protocol::ANS_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, AnsCreateArticle &rhs) {
	out << Protocol::ANS_CREATE_ART;
	if (success){
		out << Protocol:ANS_ACK;
	} else {
		out << Protocol:ANS_NAK;
		out << Protocol:ERR_NG_DOES_NOT_EXIST;
	}
	out << Protocol::ANS_END;
	return out;
}

#ifndef