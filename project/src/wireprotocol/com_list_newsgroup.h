#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__
#include "../database/newsgroup.h"

template <typename Database>
class ComListNewsgroupPacket : public ComPacket<Database>{
friend Connection& operator>>(Connection &in, ComListNewsgroupPacket &rhs);
friend Connection& operator<<(Connection &out, ComListNewsgroupPacket &rhs);
public:
	shared_ptr<AnsPacket> process(Database& db){
		vector<AnsListNewsgroupPacket::NewsGroup> newsgroups;
		for_each(db->getNewsgroupIterator(), db->getNewsgroupEnd(), 
			[&newsgroups] (const pair<uint32_t, Newsgroup> pair) {newsgroups.push_back(make_pair(pair.first, pair.second.name)); });
		shared_ptr<AnsPacket> answerPacket(new AnsListNewsgroupPacket(newsgroups));
		return answerPacket;
	}
};

void pushBackValue(pair<uint32_t, Newsgroup> pair){

}
template <typename Database>
Connection& operator>>(Connection &in, ComListNewsgroupPacket<Database> &rhs) {
	Packet::eat(in, protocol::Protocol::COM_LIST_NG);
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}

template <typename Database>
Connection& operator<<(Connection &out, ComListNewsgroupPacket<Database> &rhs) {
	out << protocol::Protocol::COM_LIST_NG;
	out << protocol::Protocol::COM_END;
	return out;
}


#endif