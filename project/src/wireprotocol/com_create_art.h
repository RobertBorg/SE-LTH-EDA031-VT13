#ifndef COM_CREATE_ART_H__
#define COM_CREATE_ART_H__

class ComCreateArtPacket : public ComPacket {
public:
	ComCreateArtPacket() = default;
	ComCreateArtPacket(uint32_t &newsGroupNumber_, string &title_, string &author_, string &text_) 
		: newsGroupNumber(newsGroupNumber_), title(title_), author(author_), text(text_) {}
	virtual shared_ptr<AnsPacket> process(Database& db) const {
		try{
			shared_ptr<Article> article(new Article());
			article->title = title;
			article->author = author;
			article->text = text;
			db->addArticle(article);
			shared_ptr<AnsPacket> answerPacket(new AnsCreateArticlePacket(true));
			return answerPacket;
		} catch (NGAlreadyExistsException){
			shared_ptr<AnsPacket> answerPacket(new AnsCreateArticlePacket(false));
			return answerPacket;
		}
	}
private:
	uint32_t newsGroupNumber;
	string title;
	string author;
	string text;
};

istream_news& operator>>(Connection &inConn, ComCreateArtPacket &rhs) {
	num_p groupNum;
	Packet::eat(in, protocol::Protocol::COM_CREATE_ART);
	string_p title:
	string_p author;
	string_p text:
	inConn >> groupNum >> title >> author >> text;
	Packet::eat(in, protocol::Protocol::COM_END);
	rhs.newsGroupNumber = groupNum;
	rhs.title = title;
	rhs.author = author;
	rhs.text = text;
	return inConn;
}

iostream_news& operator<<(Connection &outConn, ComCreateArtPacket &rhs) {
	outConn << protocol::Protocol::COM_CREATE_ART;
	outConn << num_p(rhs.newsGroupNumber);
	outConn << string_p(rhs.title);
	outConn << string_p(rhs.author);
	outConn << string_p(rhs.text);
	outConn << protocol::Protocol::COM_END;
	return outConn;
}

#endif /* end of include guard: COM_CREATE_ART_H__ */