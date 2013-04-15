#ifndef COM_DELETE_NEWSGROUP_H__
#define COM_DELETE_NEWSGROUP_H__


class ComDeleteNewsgroupPacket : public ComPacket{
public:
	shared_ptr<AnsPacket> process(Database& db){
		try{
			db->deleteNewsgroup(groupNum);
			shared_ptr<AnsPacket> answerPacket(new AnsDeleteNewsgroupPacket(true));
			return answerPacket;
		}catch (NGDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket(new AnsDeleteNewsgroupPacket(false));
			return answerPacket;
		} 
	}
	ComDeleteNewsgroupPacket(uint32_t groupNum_): groupNum(groupNum_){}
	ComDeleteNewsgroupPacket() = default;


private:
	uint32_t groupNum;
};


Connection& operator>>(Connection &inConn, ComDeleteNewsgroupPacket &rhs) {
	Packet::eat(in, protocol::COM_DELETE_NG);
	num_p num;
	inConn >> num;
	groupNum = num;
	Packet::eat(in, protocol::COM_END);
	return inConn;
}

Connection& operator<<(Connection &outConn, ComDeleteNewsgroupPacket &rhs) {
	outConn << protocol::COM_DELETE_NG;
	outConn << num_p(groupNum);
	outConn << protocol::COM_END;
	return outConn;
}


#endif