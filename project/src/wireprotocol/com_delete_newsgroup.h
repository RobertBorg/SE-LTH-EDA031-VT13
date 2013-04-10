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


Connection& operator>>(Connection &inConn, ComDeleteNewsgroupPacket &rhs) {
	eat(Protocol::COM_DELETE_NG);
	num_p num;
	inConn >> num;
	groupNum = num;
	eat(Protocol::COM_END);
	return inConn;
}

Connection& operator<<(Connection &outConn, ComDeleteNewsgroupPacket &rhs) {
	outConn << Protocol::COM_DELETE_NG;
	outConn << num_p(groupNum);
	outConn << Protocol::COM_END;
	return outConn;
}


#endif