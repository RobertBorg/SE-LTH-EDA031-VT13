#ifndef COM_DELETE_NEWSGROUP_H__
#define COM_DELETE_NEWSGROUP_H__

template <typename Database>
class ComDeleteNewsgroupPacket : public ComPacket<Database>{
template <typename Database2>
friend Connection& operator>>(Connection &in, ComDeleteNewsgroupPacket<Database2> &rhs);
template <typename Database2>
friend Connection& operator<<(Connection &out, ComDeleteNewsgroupPacket<Database2> &rhs);
public:
	virtual shared_ptr<AnsPacket> process(Database& db) const{
		try{
			db.deleteNewsgroup(groupNum);
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

template <typename Database>
Connection& operator>>(Connection &inConn, ComDeleteNewsgroupPacket<Database> &rhs) {
	Packet::eat(inConn, protocol::Protocol::COM_DELETE_NG);
	num_p num;
	inConn >> num;
	rhs.groupNum = num;
	Packet::eat(inConn, protocol::Protocol::COM_END);
	return inConn;
}

template <typename Database>
Connection& operator<<(Connection &outConn, ComDeleteNewsgroupPacket<Database> &rhs) {
	outConn << protocol::Protocol::COM_DELETE_NG;
	outConn << num_p(rhs.groupNum);
	outConn << protocol::Protocol::COM_END;
	return outConn;
}


#endif