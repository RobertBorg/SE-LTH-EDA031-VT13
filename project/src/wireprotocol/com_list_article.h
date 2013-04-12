#ifndef COM_LIST_ARTICLE_H__
#define COM_LIST_ARTICLE_H__


class ComListArticlePacket : public ComPacket{
public:
	shared_ptr<AnsPacket> process(Database& db){
		vector<Article> articles;
		for_each(db->getArticleIterator(), db->getArticleEnd(), 
			[&articles] (const pair<uint32_t, Article> pair) {articles.push_back(pair.second); });
		shared_ptr<AnsPacket> answerPacket(new AnsListArtPacket(articles));
		return answerPacket;
	}
	ComListArticlePacket() = default;
	ComListArticlePacket(int groupNum_): groupNum(groupNum_){}


private:
	int groupNum;
};


Connection& operator>>(Connection &inConn, ComListArticlePacket &rhs) {
	eat(protocol::COM_LIST_ART);
	num_p num;
	inConn >> num;
	groupNum = num;
	eat(protocol::COM_END);
	return inConn;
}

Connection& operator<<(Connection &outConn, ComListArticlePacket &rhs) {
	outConn << protocol::COM_LIST_ART;
	outConn << num_p(groupNum);
	outConn << protocol::COM_END;
	return outConn;
}



#endif