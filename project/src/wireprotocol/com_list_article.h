#ifndef COM_LIST_ARTICLE_H__
#define COM_LIST_ARTICLE_H__

#include "ans_list_art.h"
#include "../database/article.h"


template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComListArticlePacket : public ComPacket<Database, istream, ostream> {
friend istream& operator>>(istream &in, ComListArticlePacket<Database, istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::COM_LIST_ART);
	num_p num;
	in >> num;
	rhs.groupNum = num;
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}
friend ostream& operator<<(ostream &out, ComListArticlePacket<Database, istream, ostream> &rhs) {
	out << protocol::Protocol::COM_LIST_ART;
	out << num_p(rhs.groupNum);
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const {
		vector< typename AnsListArtPacket<istream, ostream>::Article > articles;
		bool success = true;
		try {
			for_each(db.getArticleBegin(groupNum), db.getArticleEnd(groupNum), 
				[&articles] (const pair<uint32_t, shared_ptr<Article> > pair) {
					articles.push_back(make_pair(pair.first, pair.second->title)); 
				});
		} catch (NGDoesntExistException& ex) {
			success = false;
		}
		shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsListArtPacket<istream, ostream>(articles, success));
		return answerPacket;
	}
	ComListArticlePacket() = default;
	ComListArticlePacket(uint32_t groupNum_): groupNum(groupNum_){}
	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	uint32_t groupNum;
};

#endif