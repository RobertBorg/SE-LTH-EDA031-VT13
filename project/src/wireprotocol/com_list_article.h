#ifndef COM_LIST_ARTICLE_H__
#define COM_LIST_ARTICLE_H__

#include "ans_list_art.h"
#include "../database/article.h"

template <typename Database>
class ComListArticlePacket : public ComPacket<Database>{
template <typename Database2>
friend Connection& operator>>(Connection &in, ComListArticlePacket<Database2> &rhs);
template <typename Database2>
friend Connection& operator<<(Connection &out, ComListArticlePacket<Database2> &rhs);
public:
	virtual shared_ptr<AnsPacket> process(Database& db) const {
		vector<AnsListArtPacket::Article> articles;
		for_each(db.getArticleBegin(groupNum), db.getArticleEnd(groupNum), 
			[&articles] (const pair<uint32_t, shared_ptr<Article> > pair) {
				articles.push_back(make_pair(pair.first, pair.second->title)); 
			});
		shared_ptr<AnsPacket> answerPacket(new AnsListArtPacket(articles));
		return answerPacket;
	}
	ComListArticlePacket() = default;
	ComListArticlePacket(uint32_t groupNum_): groupNum(groupNum_){}


private:
	uint32_t groupNum;
};

template <typename Database>
Connection& operator>>(Connection &inConn, ComListArticlePacket<Database> &rhs) {
	Packet::eat(inConn, protocol::Protocol::COM_LIST_ART);
	num_p num;
	inConn >> num;
	rhs.groupNum = num;
	Packet::eat(inConn, protocol::Protocol::COM_END);
	return inConn;
}

template <typename Database>
Connection& operator<<(Connection &outConn, ComListArticlePacket<Database> &rhs) {
	outConn << protocol::Protocol::COM_LIST_ART;
	outConn << num_p(rhs.groupNum);
	outConn << protocol::Protocol::COM_END;
	return outConn;
}



#endif