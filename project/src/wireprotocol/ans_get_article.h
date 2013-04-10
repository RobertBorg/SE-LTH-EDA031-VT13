#ifndef ANS_GET_ARTICLE_H__
#define ANS_GET_ARTICLE_H__

#include <string>

using std::string;

class AnsGetArticlePacket : public AnsPacket{
public:
	void process(){
		
	}
	AnsGetArticlePacket() = default;
	AnsGetArticlePacket(bool success_, bool ngNotFound_, bool artNotFound_, string title_, string author_, string text_) 
		: success(success_), ngNotFound(ngNotFound_), artNotFound(artNotFound_)
		, title(title_), author(author_), text(text_) {}


private:
	bool success, ngNotFound, artNotFound;
	string title, author, text;
};


Connection& operator>>(Connection &in, AnsGetArticlePacket &rhs) {
	eat(Protocol::ANS_GET_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case Protocol::ANS_ACK:
			string_p title, author, text;
			in << title << author << text;

			rhs.title = title;
			rhs.author = author;
			rhs.text = text;
			rhs.success = true;
			break;

		case Protocol:ANS_NAK:
			uint8_t errorMsg;
			in >> errorMsg;
			switch(errorMsg){
				case Protocol::ERR_NG_DOES_NOT_EXIST:
					rhs.ngNotFound = true;
					break;
				case Protocol::ERR_ART_DOES_NOT_EXIST:
					rhs.artNotFound = true;
					break
				default:
					throw ProcotolViolationException();
			}
			rhs.success = false;
			break;

		default:
			throw ProcotolViolationException();
			break;

	}
	eat(Protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsGetArticlePacket &rhs) {
	out << Protocol::ANS_GET_ART;
	if (rhs.success){
		out << Protocol:ANS_ACK;
		out << string_p(rhs.title);
		out << string_p(rhs.author);
		out << string_p(rhs.text);
	} else {
		out << Protocol:ANS_NAK;
		if (rhs.ngNotFound){
			out << Protocol:ERR_NG_DOES_NOT_EXIST;
		} else {
			out << Protocol:ERR_ART_DOES_NOT_EXIST;
		}
	}
	out << Protocol::ANS_END;
	return out;
}

#ifndef
