#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__


class ComListNewsgroupPacket : public ComPacket{
public:
	AnsPacket process(Database *db){
		
	}
};

Connection& operator>>(Connection &in, ComListPacket &rhs) {
	eat(protocol::COM_LIST_NG);
	eat(protocol::COM_END);
	return in;
}

Connection& operator<<(Connection &out, ComListPacket &rhs) {
	out << protocol::COM_LIST_NG;
	out << protocol::COM_END;
	return out;
}


#endif