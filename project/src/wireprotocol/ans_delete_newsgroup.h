#ifndef ANS_DELETE_NEWSGROUP_H__
#define ANS_DELETE_NEWSGROUP_H__


class AnsDeleteNewsgroupPacket : public AnsPacket{
public:
	void process(){
		
	}
	AnsDeleteNewsgroupPacket() = default;
	AnsDeleteNewsgroupPacket(bool success_): success(success_){}


private:
	bool success;
};


Connection& operator>>(Connection &in, AnsDeleteNewsgroupPacket &rhs) {
	in.eat(protocol::ANS_DELETE_NG);
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

Connection& operator<<(Connection &out, AnsDeleteNewsgroupPacket &rhs) {
	out << protocol::ANS_DELETE_NG;
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
