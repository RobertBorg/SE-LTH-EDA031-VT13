#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__


class ComListNewsgroupPacket : public ComPacket{
public:
	shared_ptr<AnsPacket> process(Database& db){
		vector<Newsgroup> newsgroups;
		for_each(db->getNewsgroupIterator(), db->getNewsgroupEnd(), 
			[&newsgroups] (const pair<uint32_t, Newsgroup> pair) {newsgroups.push_back(pair.second); });
		shared_ptr<AnsPacket> answerPacket(new AnsListNewsgroupPacket(newsgroups));
		return answerPacket;
	}
};

void pushBackValue(pair<uint32_t, Newsgroup> pair){

}

Connection& operator>>(Connection &in, ComListPacket &rhs) {
	Packet::eat(in, protocol::COM_LIST_NG);
	Packet::eat(in, protocol::COM_END);
	return in;
}

Connection& operator<<(Connection &out, ComListPacket &rhs) {
	out << protocol::COM_LIST_NG;
	out << protocol::COM_END;
	return out;
}


#endif