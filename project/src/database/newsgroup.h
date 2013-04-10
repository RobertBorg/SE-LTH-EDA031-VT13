#ifndef NEWSGROUP_H__
#define NEWSGROUP_H__


class Newsgroup {
public:
	Newsgroup(string name_, uint32_t id_): name(name_), id(id_){}
	vector<Article> articles;
	string name;
	uint32_t id; // Must be unique
};

#endif
