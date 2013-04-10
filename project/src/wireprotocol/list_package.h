#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__


class ComListPacket : public ComPacket{
public:
	AnsPacket process(Database *db){
		
	}
};

istream_news& operator>>(istream_news &in, ComListPacket &rhs) {
	in.eat(Protocol::COM_LIST_NG);
	in.eat(Protocol::COM_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, ComListPacket &rhs) {
	out << Protocol::COM_LIST_NG;
	out << Protocol::COM_END;
	return out;
}


#endif