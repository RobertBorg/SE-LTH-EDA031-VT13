#ifndef ANS_CREATE_NEWSGROUP_H__
#define ANS_CREATE_NEWSGROUP_H__


class AnsCreateNewsgroupPacket : public AnsPacket{
public:
	void process(){
		
	}
	AnsCreateNewsgroupPacket() = default;
	AnsCreateNewsgroupPacket(bool success_): success(success_){}


private:
	bool success;
};


istream_news& operator>>(istream_news &in, AnsCreateNewsgroupPacket &rhs) {
	in.eat(Protocol::ANS_CREATE_NG);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case Protocol:ANS_ACK:
			rhs.success = true;
			break;

		case Protocol:ANS_NAK:
			in.eat(Protocol::ERR_NG_ALREADY_EXISTS);
			rhs.success = false;
			break;

		default:
			throw ProcotolViolationException();
			break;

	}
	in.eat(Protocol::ANS_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, AnsCreateNewsgroupPacket &rhs) {
	out << Protocol::ANS_CREATE_NG;
	if (success){
		out << Protocol:ANS_ACK;
	} else {
		out << Protocol:ANS_NAK;
		out << Protocol:ERR_NG_ALREADY_EXISTS;
	}
	out << Protocol::ANS_END;
	return out;
}

#ifndef