#ifndef COM_GET_ART_H__
#define COM_GET_ART_H__
#include <memory>
using std::shared_ptr;

template <typename Database>
class ComGetArtPacket : public ComPacket<Database> {
friend Connection& operator>>(Connection &in, ComGetArtPacket &rhs);
friend Connection& operator<<(Connection &out, ComGetArtPacket &rhs);
public:
	ComGetArtPacket() = default;
	ComGetArtPacket(uint32_t &newsGroupNumber_, uint32_t &articleNumber_) : newsGroupNumber(newsGroupNumber_), articleNumber(articleNumber_) {}
	virtual shared_ptr<AnsPacket> process(Database& db) const {
		try {
			shared_ptr<Article> article = db.getArticle(articleNumber, newsGroupNumber);
			shared_ptr<AnsPacket> answerPacket = 
				AnsGetArticlePacket::createSuccessful(article->title, article->author, article->text);
			return answerPacket;
		} catch (NGDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket = AnsGetArticlePacket::createNGNotFound();
			return answerPacket;
		} catch (ArtDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket =AnsGetArticlePacket::createArtNotFound();
			return answerPacket;
		}
	}
	
private:
	uint32_t newsGroupNumber;
	uint32_t articleNumber;
};
template <typename Database>
Connection& operator>>(Connection &inConn, ComGetArtPacket<Database> &rhs) {
	Packet::eat(inConn, protocol::Protocol::COM_GET_ART);
	num_p groupNum, artNum;
	inConn >> groupNum >> artNum;
	Packet::eat(inConn, protocol::Protocol::COM_END);

	rhs.newsGroupNumber = groupNum;
	rhs.articleNumber = artNum;

	return inConn;
}
template <typename Database>
Connection& operator<<(Connection &outConn, ComGetArtPacket<Database> &rhs) {
	outConn << protocol::Protocol::COM_GET_ART;
	outConn << num_p(rhs.newsGroupNumber) << num_p(rhs.artNum);
	outConn << protocol::Protocol::COM_END;
	return outConn;
}

#endif /* end of include guard: COM_GET_ART_H__ */