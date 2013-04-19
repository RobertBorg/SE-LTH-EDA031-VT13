#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__
#include "../database/newsgroup.h"
#include "packet.h"

#include <iostream>
using std::cout;
using std::endl;
using std::for_each;

template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComListNewsgroupPacket : public ComPacket<Database, istream, ostream> {
friend Connection& operator>>(istream &in, ComListNewsgroupPacket<Database, istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::COM_LIST_NG);
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}
friend Connection& operator<<(ostream &out, ComListNewsgroupPacket<Database, istream, ostream> &rhs) {
	out << protocol::Protocol::COM_LIST_NG;
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const {
		vector<typename AnsListNewsgroupPacket<istream, ostream>::NewsGroup> newsgroups;
		for_each(db.getNewsgroupBegin(), db.getNewsgroupEnd(), 
			[&newsgroups] (pair<const uint32_t, shared_ptr<Newsgroup> > pair) {newsgroups.push_back(make_pair(pair.first, pair.second->name)); });
		shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsListNewsgroupPacket<istream, ostream>(newsgroups));
		return answerPacket;
	}

	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

};

#endif
