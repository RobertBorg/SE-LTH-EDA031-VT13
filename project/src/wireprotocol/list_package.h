#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__


class ComListPackage : public ComPackage{
public:
	AnsPackage process(Database *db){
		
	}
};

istream_news& operator>>(istream_news &in, ComListPackage &rhs) {
	in.eat(Protocol::COM_LIST_NG);
	in.eat(Protocol::COM_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, ComListPackage &rhs) {
	out << Protocol::COM_LIST_NG;
	out << Protocol::COM_END;
	return out;
}


#endif