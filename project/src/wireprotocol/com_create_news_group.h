#ifndef COM_CREATE_NEWS_GROUP_H__
#define COM_CREATE_NEWS_GROUP_H__
#include "../../lib/clientserver/protocol.h"
#include "packet.h"
#include <string>

template <typename Database>
class ComCreateNewsGroupPacket : public ComPacket<Database> {
template <typename Database2>
friend Connection& operator>>(Connection &in, ComCreateNewsGroupPacket<Database2> &rhs);
template <typename Database2>
friend Connection& operator<<(Connection &out, ComCreateNewsGroupPacket<Database2> &rhs);
public:
	ComCreateNewsGroupPacket() = default;
	ComCreateNewsGroupPacket(string newsGroupName_) : newsGroupName(newsGroupName_) {}
	virtual shared_ptr<AnsPacket> process(Database& db) const {
		try{
			shared_ptr<Newsgroup> newsGroup(new Newsgroup(0, newsGroupName));
			db.addNewsgroup(newsGroup);
			shared_ptr<AnsPacket> answerPacket(new AnsCreateNewsgroupPacket(true));
			return answerPacket;
		} catch (NGAlreadyExistsException){
			shared_ptr<AnsPacket> answerPacket(new AnsCreateNewsgroupPacket(false));
			return answerPacket;
		}
	}
private:
	string newsGroupName;
};
template <typename Database>
Connection& operator>>(Connection &inConn, ComCreateNewsGroupPacket<Database> &rhs) {
	Packet::eat(inConn, protocol::Protocol::COM_CREATE_NG);
	string_p str;
	inConn >> str;
	rhs.newsGroupName = str;
	Packet::eat(inConn, protocol::Protocol::COM_END);
	return inConn;
}
template <typename Database>
Connection& operator<<(Connection &outConn, ComCreateNewsGroupPacket<Database> &rhs) {
	outConn << protocol::Protocol::COM_CREATE_NG;
	outConn << string_p(rhs.newsGroupName);
	outConn << protocol::Protocol::COM_END;
	return outConn;
}




#endif /* end of include guard: COM_CREATE_NEWS_GROUP_H__ */
