#ifndef ANS_DELETE_NEWSGROUP_H__
#define ANS_DELETE_NEWSGROUP_H__


class AnsDeleteNewsgroupPacket : public AnsPacket{
public:
	void process(){
		
	}
	AnsDeleteNewsgroupPacket(bool success_): success(success_){}


private:
	bool success;
};


istream_news& operator>>(istream_news &in, AnsDeleteNewsgroupPacket &rhs) {
	in.eat(Protocol::ANS_DELETE_NG);
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

iostream_news& operator<<(iostream_news &out, AnsDeleteNewsgroupPacket &rhs) {
	out << Protocol::ANS_DELETE_NG;
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
