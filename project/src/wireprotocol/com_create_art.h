#ifndef COM_CREATE_ART_H__
#define COM_CREATE_ART_H__

class ComCreateArtPacket : public ComPacket {
public:
	ComCreateArtPacket() = default;
	ComCreateArtPacket(int &newsGroupNumber_, string &title_, string &author_, string &text_) 
		: newsGroupNumber(newsGroupNumber_), title(title_), author(author_), text(text_) {}
	virtual shared_ptr<AnsPacket> process(Database& db) const {

	}
private:
	int newsGroupNumber;
	string title;
	string author;
	string text;
};

istream_news& operator>>(Connection &inConn, ComCreateArtPacket &rhs) {
	num_p groupNum;
	eat(protocol::COM_CREATE_ART);
	string_p title:
	string_p author;
	string_p text:
	inConn >> groupNum >> title >> author >> text;
	eat(protocol::COM_END);
	rhs.newsGroupNumber = groupNum;
	rhs.title = title;
	rhs.author = author;
	rhs.text = text;
	return inConn;
}

iostream_news& operator<<(Connection &outConn, ComCreateArtPacket &rhs) {
	outConn << protocol::COM_CREATE_ART;
	outConn << num_p(rhs.newsGroupNumber);
	outConn << string_p(rhs.title);
	outConn << string_p(rhs.author);
	outConn << string_p(rhs.text);
	outConn << protocol::COM_END;
	return outConn;
}

#endif /* end of include guard: COM_CREATE_ART_H__ */