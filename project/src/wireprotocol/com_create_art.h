#ifndef COM_CREATE_ART_H__
#define COM_CREATE_ART_H__

class ComCreateArt : public ComPackage {
public:
	ComCreateArt(int &newsGroupNumber_, string &title_, string &author_, string &text_) 
		: newsGroupNumber(newsGroupNumber_), title(title_), author(author_), text(text_) {}
	virtual shared_ptr<AnsPackage> process(Database *db) const {

	}
private:
	int newsGroupNumber;
	string title;
	string author;
	string text;
};

istream_news& operator>>(istream_news &in, ComCreateArt &rhs) {
	COM_CREATE_ART num_p string_p string_p string_p COM_END
	num_p groupNum;
	in.eat(protocol::COM_CREATE_ART);
	string_p title:
	string_p author;
	string_p text:
	in >> groupNum >> title >> author >> text;
	in.eat(protocol::COM_END);
	rhs.newsGroupNumber = groupNum;
	rhs.title = title;
	rhs.author = author;
	rhs.text = text;
	return in;
}

iostream_news& operator<<(iostream_news &out, ComCreateArt &rhs) {
	out << protocol::COM_CREATE_ART;
	out << num_p(rhs.newsGroupNumber);
	out << string_p(rhs.title);
	out << string_p(rhs.author);
	out << string_p(rhs.text);
	out << protocol::COM_END;
	return out;
}

#endif /* end of include guard: COM_CREATE_ART_H__ */