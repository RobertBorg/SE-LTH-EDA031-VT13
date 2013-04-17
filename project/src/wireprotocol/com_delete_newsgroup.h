#ifndef COM_DELETE_NEWSGROUP_H__
#define COM_DELETE_NEWSGROUP_H__

template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComDeleteNewsgroupPacket : public ComPacket<Database, istream, ostream>{
friend istream& operator>>(istream &in, ComDeleteNewsgroupPacket<Database, istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::COM_DELETE_NG);
	num_p num;
	in >> num;
	rhs.groupNum = num;
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}
friend ostream& operator<<(ostream &out, ComDeleteNewsgroupPacket<Database, istream, ostream> &rhs) {
	out << protocol::Protocol::COM_DELETE_NG;
	out << num_p(rhs.groupNum);
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const{
		try{
			db.deleteNewsgroup(groupNum);
			shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsDeleteNewsgroupPacket<istream, ostream>(true));
			return answerPacket;
		}catch (NGDoesntExistException e){
			shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsDeleteNewsgroupPacket<istream, ostream>(false));
			return answerPacket;
		} 
	}
	ComDeleteNewsgroupPacket(uint32_t groupNum_): groupNum(groupNum_){}
	ComDeleteNewsgroupPacket() = default;
	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	uint32_t groupNum;
};

#endif