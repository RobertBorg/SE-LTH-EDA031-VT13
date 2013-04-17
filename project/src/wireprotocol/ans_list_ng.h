#ifndef ANS_LIST_NG_H__
#define ANS_LIST_NG_H__
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <memory>
using std::shared_ptr;
#include "packet.h"

#include <iostream>
using std::cout;
using std::endl;

template <typename istream, typename ostream>
class AnsListNewsgroupPacket : public AnsPacket<istream, ostream> {
friend istream& operator>>(istream &in, AnsListNewsgroupPacket<istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_LIST_NG);
	num_p numNG;
	in >> numNG;
	for(unsigned int i = 0 ;i < numNG.value; ++i){
		num_p id;
		string_p str;
		in >> id >> str;
		rhs.newsGroups.push_back(make_pair(id.value, str));
	}
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}
friend ostream& operator<<(ostream &out, AnsListNewsgroupPacket<istream, ostream> &rhs){
	out << protocol::Protocol::proto::ANS_LIST_NG;
	out << num_p(static_cast<int>(rhs.newsGroups.size()));
	for(AnsListNewsgroupPacket::NewsGroup ng : rhs.newsGroups) {
		out << num_p(ng.first);
		out << string_p(ng.second);
	}
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	typedef pair<uint32_t, string> NewsGroup;
	typedef vector<NewsGroup> NewsGroups;
	AnsListNewsgroupPacket() = default;
	AnsListNewsgroupPacket(NewsGroups &newsGroups_) : newsGroups(newsGroups_) {}
	virtual void process() const {
		if(this->newsGroups.size() != 0){
			for (NewsGroup ng : this->newsGroups) {
				cout <<"Id :" << ng.first << " Name: " << ng.second << endl;
			}
		} else {
			cout << "There are no newsgroups." << endl;
		}
	}

	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	NewsGroups newsGroups;
};

#endif /* end of include guard: ANS_LIST_NG_H__ */