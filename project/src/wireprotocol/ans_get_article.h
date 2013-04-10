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


	static &AnsGetArticlePacket createSuccessful(string title, string author, string text){
		return new AnsGetArticlePacket(true, false, false title, author, text);
	}
	static &AnsGetArticlePacket createNGNotFound(){
		return new AnsGetArticlePacket(false, true, false nullptr, nullptr, nullptr);
	}
	static &AnsGetArticlePacket createArtNotFound(){
		return new AnsGetArticlePacket(false, false, true nullptr, nullptr, nullptr);
	}


private:
	bool success, ngNotFound, artNotFound;
	string title, author, text;
};


Connection& operator>>(Connection &in, AnsGetArticlePacket &rhs) {
	eat(protocol::ANS_GET_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol::ANS_ACK:
			string_p title, author, text;
			in << title << author << text;

			rhs.title = title;
			rhs.author = author;
			rhs.text = text;
			rhs.success = true;
			break;

		case protocol:ANS_NAK:
			uint8_t errorMsg;
			in >> errorMsg;
			switch(errorMsg){
				case protocol::ERR_NG_DOES_NOT_EXIST:
					rhs.ngNotFound = true;
					break;
				case protocol::ERR_ART_DOES_NOT_EXIST:
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
	eat(protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsGetArticlePacket &rhs) {
	out << protocol::ANS_GET_ART;
	if (rhs.success){
		out << protocol:ANS_ACK;
		out << string_p(rhs.title);
		out << string_p(rhs.author);
		out << string_p(rhs.text);
	} else {
		out << protocol:ANS_NAK;
		if (rhs.ngNotFound){
			out << protocol:ERR_NG_DOES_NOT_EXIST;
		} else {
			out << protocol:ERR_ART_DOES_NOT_EXIST;
		}
	}
	out << protocol::ANS_END;
	return out;
}

#ifndef
