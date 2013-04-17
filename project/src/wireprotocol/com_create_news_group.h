#ifndef COM_CREATE_NEWS_GROUP_H__
#define COM_CREATE_NEWS_GROUP_H__

#include "../../lib/clientserver/protocol.h"
#include "packet.h"
#include <string>

template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComCreateNewsGroupPacket : public ComPacket<Database, istream, ostream> {
friend istream& operator>>(istream &in, ComCreateNewsGroupPacket<Database, istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::COM_CREATE_NG);
	string_p str;
	in >> str;
	rhs.newsGroupName = str;
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}
friend ostream& operator<<(ostream &out, ComCreateNewsGroupPacket<Database, istream, ostream> &rhs) {
	out << protocol::Protocol::COM_CREATE_NG;
	out << string_p(rhs.newsGroupName);
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	ComCreateNewsGroupPacket() = default;
	ComCreateNewsGroupPacket(string newsGroupName_) : newsGroupName(newsGroupName_) {}
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const {
		try{
			shared_ptr<Newsgroup> newsGroup(new Newsgroup(0, newsGroupName));
			db.addNewsgroup(newsGroup);
			shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsCreateNewsgroupPacket<istream, ostream>(true));
			return answerPacket;
		} catch (NGAlreadyExistsException){
			shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsCreateNewsgroupPacket<istream, ostream>(false));
			return answerPacket;
		}
	}

	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}
	
private:
	string newsGroupName;
};

#endif /* end of include guard: COM_CREATE_NEWS_GROUP_H__ */
