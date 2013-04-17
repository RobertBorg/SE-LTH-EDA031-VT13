#ifndef COM_CREATE_ART_H__
#define COM_CREATE_ART_H__
#include "packet.h"
#include "../database/database_exceptions.h"

template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComCreateArtPacket : public ComPacket<Database, istream, ostream> {
friend istream& operator>>(istream &in, ComCreateArtPacket<Database, istream, ostream> &rhs) {
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
friend ostream& operator<<(ostream &out, ComCreateArtPacket<Database, istream, ostream> &rhs) {
	out << protocol::Protocol::COM_CREATE_ART;
	out << num_p(rhs.newsGroupNumber);
	out << string_p(rhs.title);
	out << string_p(rhs.author);
	out << string_p(rhs.text);
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	ComCreateArtPacket() = default;
	ComCreateArtPacket(const uint32_t &newsGroupNumber_, const string &title_, const string &author_, const string &text_) 
		: newsGroupNumber(newsGroupNumber_), title(title_), author(author_), text(text_) {}
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const {
		try{
			shared_ptr<Article> article(new Article());
			article->title = title;
			article->author = author;
			article->text = text;
			article->newsgroupId = newsGroupNumber;
			db.addArticle(article);
			shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsCreateArticlePacket<istream, ostream>(true));
			return answerPacket;
		} catch (NGDoesntExistException &ex){
			shared_ptr<AnsPacket<istream, ostream>> answerPacket(new AnsCreateArticlePacket<istream, ostream>(false));
			return answerPacket;
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
	string title;
	string author;
	string text;
};

#endif /* end of include guard: COM_CREATE_ART_H__ */