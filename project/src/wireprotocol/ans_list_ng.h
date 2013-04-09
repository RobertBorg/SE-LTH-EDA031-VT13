#ifndef ANS_LIST_NG_H__
#define ANS_LIST_NG_H__
#include <string>
using std::string;
#include <utility>
using std::pair;

class AnsListNG : public AnsPackage {
public:
	typedef pair<int, string> NewsGroup;
	typedef vector<NewsGroup> NewsGroups;
	AnsListNG(NewsGroups &newsGroups_) : newsGroups(newsGroups_) {}
	virtual void process() const {

	}
private:
	NewsGroups newsGroups;
};

istream_news& operator>>(istream_news &in, AnsListNG &rhs) {
	in.eat(protocol::ANS_LIST_NG);
	num_p numNG;
	in >> numNG;
	for(int i = 0 i < numNG; ++i){
		num_p id;
		string_p str;
		in >> id >> str;
		rhs.newsGroups.push_back(NewsGroup(id,str));
	}
	in.eat(protocol::COM_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, AnsListNG &rhs) {
	out << protocol::ANS_LIST_NG;
	out << num_p(static_cast<int>(rhs.newsGroups.size()));
	for(NewsGroup ng : rhs.newsGroups) {
		out << num_p(ng.first);
		out << string_p(ng.second);
	}
	out << protocol::COM_END;
	return out;
}

#endif /* end of include guard: ANS_LIST_NG_H__ */