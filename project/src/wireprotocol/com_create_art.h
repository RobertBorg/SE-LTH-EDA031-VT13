#ifndef COM_CREATE_ART_H__
#define COM_CREATE_ART_H__
#include "packet.h"
template< typename Database>
class ComCreateArtPacket : public ComPacket<Database> {
friend Connection& operator>>(Connection &in, ComCreateArtPacket &rhs);
friend Connection& operator<<(Connection &out, ComCreateArtPacket &rhs);
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
template < typename Database>
Connection& operator>>(Connection &in, ComCreateArtPacket<Database> &rhs) {
	num_p groupNum;
	Packet::eat(in, protocol::Protocol::COM_CREATE_ART);
	string_p title;
	string_p author;
	string_p text;
	in >> groupNum >> title >> author >> text;
	Packet::eat(in, protocol::Protocol::COM_END);
	rhs.newsGroupNumber = groupNum;
	rhs.title = title;
	rhs.author = author;
	rhs.text = text;
	return in;
}

template < typename Database>
Connection& operator<<(Connection &out, ComCreateArtPacket<Database> &rhs) {
	out << protocol::Protocol::COM_CREATE_ART;
	out << num_p(rhs.newsGroupNumber);
	out << string_p(rhs.title);
	out << string_p(rhs.author);
	out << string_p(rhs.text);
	out << protocol::Protocol::COM_END;
	return out;
}

#endif /* end of include guard: COM_CREATE_ART_H__ */