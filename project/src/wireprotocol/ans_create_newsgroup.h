#ifndef ANS_CREATE_NEWSGROUP_H__
#define ANS_CREATE_NEWSGROUP_H__


class AnsCreateNewsgroupPacket : public AnsPacket{
public:
	void process(){
		if (success){
			cout << "Newsgroup successfully created." << endl;
		} else {
			cout << "Newsgroup with that name already exists." << endl;
		}
	}
	AnsCreateNewsgroupPacket() = default;
	AnsCreateNewsgroupPacket(bool success_): success(success_){}


private:
	bool success;
};


Connection& operator>>(Connection &in, AnsCreateNewsgroupPacket &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_CREATE_NG);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol:ANS_ACK:
			rhs.success = true;
			break;

		case protocol:ANS_NAK:
			Packet::eat(in, protocol::Protocol::ERR_NG_ALREADY_EXISTS);
			rhs.success = false;
			break;

		default:
			throw ProcotolViolationException();
			break;

	}
	Packet::eat(in, protocol::Protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsCreateNewsgroupPacket &rhs) {
	out << protocol::Protocol::ANS_CREATE_NG;
	if (success){
		out << protocol:ANS_ACK;
	} else {
		out << protocol:ANS_NAK;
		out << protocol:ERR_NG_ALREADY_EXISTS;
	}
	out << protocol::Protocol::ANS_END;
	return out;
}

#ifndef