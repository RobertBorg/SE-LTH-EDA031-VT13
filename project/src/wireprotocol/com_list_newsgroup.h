#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__


class ComListNewsgroupPacket : public ComPacket{
public:
	AnsPacket process(Database *db){
		
	}
};

Connection& operator>>(Connection &in, ComListPacket &rhs) {
	eat(Protocol::COM_LIST_NG);
	eat(Protocol::COM_END);
	return in;
}

Connection& operator<<(Connection &out, ComListPacket &rhs) {
	out << Protocol::COM_LIST_NG;
	out << Protocol::COM_END;
	return out;
}


#endif