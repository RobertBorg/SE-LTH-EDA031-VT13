#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__
#include "../database/newsgroup.h"

#include <iostream>
using std::cout;
using std::endl;

template <typename Database>
class ComListNewsgroupPacket : public ComPacket<Database>{
template <typename Database2>
friend Connection& operator>>(Connection &in, ComListNewsgroupPacket<Database2> &rhs);
template <typename Database2>
friend Connection& operator<<(Connection &out, ComListNewsgroupPacket<Database2> &rhs);
public:
	virtual shared_ptr<AnsPacket> process(Database& db) const {
		vector<AnsListNewsgroupPacket::NewsGroup> newsgroups;
		for_each(db.getNewsgroupBegin(), db.getNewsgroupEnd(), 
			[&newsgroups] (pair<const uint32_t, shared_ptr<Newsgroup> > pair) {newsgroups.push_back(make_pair(pair.first, pair.second->name)); });
		shared_ptr<AnsPacket> answerPacket(new AnsListNewsgroupPacket(newsgroups));
		return answerPacket;
	}
};

template <typename Database>
Connection& operator>>(Connection &in, ComListNewsgroupPacket<Database> &rhs) {
	cout << "starting parsing in operator >>" << endl;
	Packet::eat(in, protocol::Protocol::COM_LIST_NG);
	Packet::eat(in, protocol::Protocol::COM_END);
	cout << "parsing ok" << endl;
	return in;
}

template <typename Database>
Connection& operator<<(Connection &out, ComListNewsgroupPacket<Database> &rhs) {
	uint8_t a =protocol::Protocol::COM_LIST_NG;
	out << a;
	a =protocol::Protocol::COM_END;
	out << a;
	return out;
}


#endif