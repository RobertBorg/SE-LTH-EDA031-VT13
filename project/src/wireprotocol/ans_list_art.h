#ifndef ANS_LIST_ART_H__
#define ANS_LIST_ART_H__
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <vector>
using std::vector;
#include "packet.h"

template <typename istream, typename ostream>
class AnsListArtPacket : public AnsPacket<istream, ostream> {
friend istream& operator>>(istream &in, AnsListArtPacket<istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_LIST_ART);
	uint8_t success;
	in >> success;
	switch(success) {
		case protocol::Protocol::ANS_ACK:
			rhs.newsGroupExists = true;
			num_p num;
			in >> num;
			for( unsigned int i = 0; i < num.value; ++i) {
				num_p id;
				string_p title;
				in >> id >> title;
				rhs.articles.push_back(make_pair(id, title));
			}
			break;
		case protocol::Protocol::ANS_NAK:
			Packet::eat(in, protocol::Protocol::ERR_NG_DOES_NOT_EXIST);
			rhs.newsGroupExists = false;
			break;
		default:
			throw SeralizationViolationException();
	}
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}
friend ostream& operator<<(ostream &out, AnsListArtPacket<istream, ostream> &rhs) {
	out << protocol::Protocol::ANS_LIST_ART;
	if(rhs.newsGroupExists) {
		out << protocol::Protocol::ANS_ACK;
		out << num_p(static_cast<int>(rhs.articles.size()));
		for(AnsListArtPacket::Article a : rhs.articles) {
			out << num_p(a.first);
			out << string_p(a.second);
		}
	} else {
		out << protocol::Protocol::ANS_NAK << protocol::Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	typedef pair<int, string> Article;
	typedef vector<Article> Articles;
	AnsListArtPacket() = default;
	AnsListArtPacket(Articles &newsGroups_, bool &newsGroupExists_) : articles(newsGroups_), newsGroupExists(newsGroupExists_) {}
	virtual void process() const {
		if(newsGroupExists) {
			cout << "there are " << this->articles.size() << " articles in newsgroup." << endl;
			for (Article art : this->articles){
				cout << "Id: " << art.first << " Title: " << art.second << endl;
			}
		} else {
			cout << "there is no such newsgroup" << endl;
		}
	}

	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	vector<Article> articles;
	bool newsGroupExists;
};

#endif /* end of include guard: ANS_LIST_ART_H__ */