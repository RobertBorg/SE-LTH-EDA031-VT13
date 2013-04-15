#ifndef ANS_LIST_NG_H__
#define ANS_LIST_NG_H__
#include <string>
using std::string;
#include <utility>
using std::pair;
#include "packet.h"

class AnsListNewsgroupPacket : public AnsPacket {
public:
	typedef pair<int, string> NewsGroup;
	typedef vector<NewsGroup> NewsGroups;
	AnsListNewsgroupPacket() = default;
	AnsListNewsgroupPacket(NewsGroups &newsGroups_) : newsGroups(newsGroups_) {}
	virtual void process() const {
		for (NewsGroup ng : newsGroups) {
			cout <<"Id :" << ng.first << " Name: " << ng.second << endl;
		}
	}
private:
	NewsGroups newsGroups;
};

Connection& operator>>(Connection &in, AnsListNewsgroupPacket &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_LIST_NG);
	num_p numNG;
	in >> numNG;
	for(int i = 0 i < numNG; ++i){
		num_p id;
		string_p str;
		in >> id >> str;
		rhs.newsGroups.push_back(NewsGroup(id,str));
	}
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}

Connection& operator<<(Connection &out, AnsListNewsgroupPacket &rhs) {
	out << protocol::Protocol::ANS_LIST_NG;
	out << num_p(static_cast<int>(rhs.newsGroups.size()));
	for(NewsGroup ng : rhs.newsGroups) {
		out << num_p(ng.first);
		out << string_p(ng.second);
	}
	out << protocol::Protocol::COM_END;
	return out;
}

#endif /* end of include guard: ANS_LIST_NG_H__ */