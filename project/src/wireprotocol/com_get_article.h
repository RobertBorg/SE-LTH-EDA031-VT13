#ifndef COM_GET_ART_H__
#define COM_GET_ART_H__

#include <memory>
using std::shared_ptr;
using std::dynamic_pointer_cast;


template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComGetArtPacket : public ComPacket<Database, istream, ostream> {
friend istream& operator>>(istream &in, ComGetArtPacket<Database, istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::COM_GET_ART);
	num_p groupNum, artNum;
	in >> groupNum >> artNum;
	Packet::eat(in, protocol::Protocol::COM_END);

	rhs.newsGroupNumber = groupNum;
	rhs.articleNumber = artNum;

	return in;
}
friend ostream& operator<<(ostream &out, ComGetArtPacket<Database, istream, ostream> &rhs) {
	out << protocol::Protocol::COM_GET_ART;
	out << num_p(rhs.newsGroupNumber) << num_p(rhs.articleNumber);
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	ComGetArtPacket() = default;
	ComGetArtPacket(const uint32_t &newsGroupNumber_, const uint32_t &articleNumber_) : newsGroupNumber(newsGroupNumber_), articleNumber(articleNumber_) {}
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const {
		try {
			shared_ptr<Article> article = db.getArticle(articleNumber, newsGroupNumber);
			shared_ptr<AnsPacket<istream, ostream>> answerPacket = 
				dynamic_pointer_cast<AnsPacket<istream, ostream> >(AnsGetArticlePacket<istream, ostream>::createSuccessful(article->title, article->author, article->text));
			return answerPacket;
		} catch (NGDoesntExistException e){
			shared_ptr<AnsPacket<istream, ostream>> answerPacket = AnsGetArticlePacket<istream, ostream>::createNGNotFound();
			return dynamic_pointer_cast<AnsGetArticlePacket<istream, ostream> >(answerPacket);
		} catch (ArtDoesntExistException e){
			shared_ptr<AnsPacket<istream, ostream>> answerPacket =AnsGetArticlePacket<istream, ostream>::createArtNotFound();
			return dynamic_pointer_cast<AnsGetArticlePacket<istream, ostream> >(answerPacket);
		}
	}
	
	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}
	
private:
	uint32_t newsGroupNumber;
	uint32_t articleNumber;
};

#endif /* end of include guard: COM_GET_ART_H__ */