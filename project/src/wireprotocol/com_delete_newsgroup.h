#ifndef COM_DELETE_NEWSGROUP_H__
#define COM_DELETE_NEWSGROUP_H__


class ComDeleteNewsgroupPacket : public ComPacket{
public:
	AnsPacket process(Database *db){
		
	}
	ComDeleteNewsgroupPacket(int groupNum_): groupNum(groupNum_){}
	ComDeleteNewsgroupPacket() = default;


private:
	int groupNum;
};


istream_news& operator>>(istream_news &in, ComDeleteNewsgroupPacket &rhs) {
	in.eat(Protocol::COM_DELETE_NG);
	num_p num;
	in >> num;
	groupNum = num;
	in.eat(Protocol::COM_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, ComDeleteNewsgroupPacket &rhs) {
	out << Protocol::COM_DELETE_NG;
	out << num_p(groupNum);
	out << Protocol::COM_END;
	return out;
}


#endif