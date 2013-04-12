#ifndef COM_GET_ART_H__
#define COM_GET_ART_H__

class ComGetArtPacket : public ComPacket {
public:
	ComGetArtPacket() = default;
	ComGetArtPacket(uint32_t &newsGroupNumber_, uint32_t &articleNumber_) : newsGroupNumber(newsGroupNumber_), articleNumber(articleNumber_) {}
	virtual shared_ptr<AnsPacket> process(Database& db) const {
		try {
			shared_ptr<Article> article = db->getArticle(articleNumber, newsGroupNumber);
			shared_ptr<AnsPacket> answerPacket(
				AnsGetArticlePacket::createSuccessful(article->title, article->author, article->text));
			return answerPacket;
		} catch (NGDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket(AnsGetArticlePacket::createNGNotFound());
			return answerPacket;
		} catch (ArtDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket(AnsGetArticlePacket::createArtNotFound());
			return answerPacket;
		}
	}
	
private:
	uint32_t newsGroupNumber;
	uint32_t articleNumber;
};

Connection& operator>>(Connection &inConn, ComGetArtPacket &rhs) {
	eat(protocol::COM_GET_ART);
	num_p groupNum, artNum;
	inConn >> groupNum >> artNum;
	eat(protocol::COM_END);

	newsGroupNumber = groupNum;
	articleNumber = artNum;

	return in;
}

Connection& operator<<(Connection &outConn, ComGetArtPacket &rhs) {
	outConn << protocol::COM_GET_ART;
	outConn << num_p(newsGroupNumber) << num_p(artNum);
	outConn << protocol::COM_END;
	return outConn;
}

#endif /* end of include guard: COM_GET_ART_H__ */