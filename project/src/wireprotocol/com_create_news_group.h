#ifndef COM_CREATE_NEWS_GROUP_H__
#define COM_CREATE_NEWS_GROUP_H__
#include "../../lib/clientserver/protocol.h"
#include "package.h"
#include <string>

class ComCreateNewsGroup : public ComPackage {
public:
	ComCreateNewsGroup(string newsGroupName_) : newsGroupName(newsGroupName_) {}
	virtual shared_ptr<AnsPackage> process(Database *db) const {

	}
private:
	string newsGroupName;
};

istream_news& operator>>(istream_news &in, ComCreateNewsGroup &rhs) {
	in.eat(protocol::COM_CREATE_NG);
	string_p str;
	in >> str;
	newsGroupName = str;
	in.eat(protocol::COM_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, ComCreateNewsGroup &rhs) {
	out << protocol::COM_CREATE_NG;
	out << string_p(newsGroupName);
	out << protocol::COM_END;
	return out;
}




#endif /* end of include guard: COM_CREATE_NEWS_GROUP_H__ */