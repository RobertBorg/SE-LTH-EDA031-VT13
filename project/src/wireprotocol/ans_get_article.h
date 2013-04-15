#ifndef ANS_GET_ARTICLE_H__
#define ANS_GET_ARTICLE_H__

#include <string>
#include "packet.h"
#include "string_p.h"
#include "num_p.h"

using std::string;

class AnsGetArticlePacket : public AnsPacket{
friend Connection& operator>>(Connection &in, AnsGetArticlePacket &rhs);
friend Connection& operator<<(Connection &out, AnsGetArticlePacket &rhs);
public:
	void process(){
		if (this->success){
			cout << "Title: " << title << endl << 
			"Author: " << author << endl <<
			"Text: " << text << endl;
		} else if (this->ngNotFound){
			cout << "Newsgroup not found...";
		} else if (this->artNotFound){
			cout << "Article not found...";
		}
		
	}
	AnsGetArticlePacket() = default;
	AnsGetArticlePacket(bool success_, bool ngNotFound_, bool artNotFound_, string title_, string author_, string text_) 
		: success(success_), ngNotFound(ngNotFound_), artNotFound(artNotFound_)
		, title(title_), author(author_), text(text_) {}


	static shared_ptr<AnsGetArticlePacket> createSuccessful(string title, string author, string text){
		return shared_ptr<AnsGetArticlePacket>(new AnsGetArticlePacket(true, false, false, title, author, text));
	}
	static shared_ptr<AnsGetArticlePacket> createNGNotFound(){
		return shared_ptr<AnsGetArticlePacket>(new AnsGetArticlePacket(false, true, false, nullptr, nullptr, nullptr));
	}
	static shared_ptr<AnsGetArticlePacket> createArtNotFound(){
		return shared_ptr<AnsGetArticlePacket>(new AnsGetArticlePacket(false, false, true, nullptr, nullptr, nullptr));
	}


private:
	bool success, ngNotFound, artNotFound;
	string title, author, text;
};


Connection& operator>>(Connection &in, AnsGetArticlePacket &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_GET_ART);
	uint8_t selection;
	in >> selection;
	switch(selection){
		case protocol::Protocol::ANS_ACK:{
			
			string_p title, author, text;
			in << title << author << text;

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
					throw ProtocolViolationException();
				}
			}
			rhs.success = false;
			break;

		}
		default:{

			throw ProtocolViolationException();
			break;
		}

	}
	Packet::eat(in, protocol::Protocol::ANS_END);
	return in;
}

Connection& operator<<(Connection &out, AnsGetArticlePacket &rhs) {
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

#endif
