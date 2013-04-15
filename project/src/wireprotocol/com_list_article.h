#ifndef COM_LIST_ARTICLE_H__
#define COM_LIST_ARTICLE_H__

#include "ans_list_art.h"
#include "../database/article.h"

template <typename Database>
class ComListArticlePacket : public ComPacket<Database>{
friend Connection& operator>>(Connection &in, ComListArticlePacket &rhs);
friend Connection& operator<<(Connection &out, ComListArticlePacket &rhs);
public:
	shared_ptr<AnsPacket> process(Database& db){
		vector<AnsListArtPacket::Article> articles;
		for_each(db->getArticleIterator(), db->getArticleEnd(), 
			[&articles] (const pair<uint32_t, Article> pair) {articles.push_back(make_pair(pair.first, pair.second.title)); });
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