#ifndef ANS_GET_ARTICLE_H__
#define ANS_GET_ARTICLE_H__

#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include "packet.h"
#include "string_p.h"
#include "num_p.h"


template <typename istream, typename ostream>
class AnsGetArticlePacket : public AnsPacket<istream, ostream> {
friend istream& operator>>(istream &in, AnsGetArticlePacket<istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_GET_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol::Protocol::ANS_ACK:{
			
			string_p title, author, text;
			in >> title >> author >> text;

			rhs.title = title;
			rhs.author = author;
			rhs.text = text;
			rhs.success = true;
			break;

		}
		case protocol::Protocol::ANS_NAK:
		{

			uint8_t errorMsg;
			in >> errorMsg;
			switch(errorMsg){
				case protocol::Protocol::ERR_NG_DOES_NOT_EXIST:
				{

					rhs.ngNotFound = true;
					break;
				}
				case protocol::Protocol::ERR_ART_DOES_NOT_EXIST:
				{
					rhs.artNotFound = true;
					break;
				}
				default:
				{
					throw SeralizationViolationException();
				}
			}
			rhs.success = false;
			break;

		}
		default:{

			throw SeralizationViolationException();
			break;
		}

	}
	Packet::eat(in, protocol::Protocol::ANS_END);
	return in;
}
friend ostream& operator<<(ostream &out, AnsGetArticlePacket<istream, ostream> &rhs) {
	out << protocol::Protocol::ANS_GET_ART;
	if (rhs.success){
		out << protocol::Protocol::ANS_ACK;
		out << string_p(rhs.title);
		out << string_p(rhs.author);
		out << string_p(rhs.text);
	} else {
		out << protocol::Protocol::ANS_NAK;
		if (rhs.ngNotFound){
			out << protocol::Protocol::ERR_NG_DOES_NOT_EXIST;
		} else {
			out << protocol::Protocol::ERR_ART_DOES_NOT_EXIST;
		}
	}
	out << protocol::Protocol::ANS_END;
	return out;
}
public:
	virtual void process() const{
		if (this->success){
			cout << "Title: " << title << endl << 
			"Author: " << author << endl <<
			"Text: " << text << endl;
		} else if (this->ngNotFound){
			cout << "Newsgroup not found..." << endl;
		} else if (this->artNotFound){
			cout << "Article not found..." << endl;
		}
		
	}
	AnsGetArticlePacket() = default;
	AnsGetArticlePacket(bool success_, bool ngNotFound_, bool artNotFound_)
		: success(success_), ngNotFound(ngNotFound_), artNotFound(artNotFound_) {}
	AnsGetArticlePacket(bool success_, bool ngNotFound_, bool artNotFound_, string title_, string author_, string text_) 
		: success(success_), ngNotFound(ngNotFound_), artNotFound(artNotFound_)
		, title(title_), author(author_), text(text_) {}


	static shared_ptr<AnsGetArticlePacket<istream, ostream>> createSuccessful(string title, string author, string text){
		return shared_ptr<AnsGetArticlePacket<istream, ostream>>(new AnsGetArticlePacket<istream, ostream>(true, false, false, title, author, text));
	}
	static shared_ptr<AnsGetArticlePacket<istream, ostream>> createNGNotFound(){
		return shared_ptr<AnsGetArticlePacket<istream, ostream>>(new AnsGetArticlePacket<istream, ostream>(false, true, false));
	}
	static shared_ptr<AnsGetArticlePacket<istream, ostream>> createArtNotFound(){
		return shared_ptr<AnsGetArticlePacket<istream, ostream>>(new AnsGetArticlePacket<istream, ostream>(false, false, true));
	}

	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	bool success, ngNotFound, artNotFound;
	string title, author, text;
};

#endif
