#ifndef COM_CREATE_NEWS_GROUP_H__
#define COM_CREATE_NEWS_GROUP_H__
#include "../../lib/clientserver/protocol.h"
#include "package.h"
#include <string>

class ComCreateNewsGroupPacket : public ComPacket {
public:
	ComCreateNewsGroupPacket() = default;
	ComCreateNewsGroupPacket(string newsGroupName_) : newsGroupName(newsGroupName_) {}
	virtual shared_ptr<AnsPacket> process(Database *db) const {

	}
private:
	string newsGroupName;
};

Connection& operator>>(Connection &inConn, ComCreateNewsGroupPacket &rhs) {
	eat(protocol::COM_CREATE_NG);
	string_p str;
	inConn >> str;
	newsGroupName = str;
	eat(protocol::COM_END);
	return inConn;
}

Connection& operator<<(Connection &outConn, ComCreateNewsGroupPacket &rhs) {
	outConn << protocol::COM_CREATE_NG;
	outConn << string_p(newsGroupName);
	outConn << protocol::COM_END;
	return outConn;
}




#endif /* end of include guard: COM_CREATE_NEWS_GROUP_H__ */
