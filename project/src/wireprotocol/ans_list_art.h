#ifndef ANS_LIST_ART_H__
#define ANS_LIST_ART_H__
#include <string>
using std::string;
#include <utility>
using std::pair;

class AnsListArtPacket : public AnsPacket {
public:
	typedef pair<int, string> Article;
	typedef vector<Article> Articles;
	AnsListArtPacket() = default;
	AnsListArtPacket(Articles &newsGroups_) : articles(newsGroups_) {}
	virtual void process() const {
		for (Article art : articles){
			cout << "Id: " << art.first << " Title: " << art.second << endl;
		}
	}
private:
	Articles articles;
};

Connection& operator>>(Connection &in, AnsListArtPacket &rhs) {
	Packet::eat(in, protocol::Protocol::ANS_LIST_ART);
	uint8_t success;
	switch(success) {
		case protocol::Protocol::ANS_ACK:
			num_p num;
			in >> num;
			for( int i = 0; i < num; ++i) {
				num_p id;
				string_p title;
				in >> id >> title;
				rhs.articles.push_back(Article(id,title));
			}
			break;
		case protocol::Protocol::ANS_NAK:
			Packet::eat(in, protocol::Protocol::ERR_NG_DOES_NOT_EXIST]);
			break;
		default:
			throw ProtocolViolationException();
	}
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}

Connection& operator<<(Connection &out, AnsListArtPacket &rhs) {
	out << protocol::Protocol::ANS_LIST_ART;
	out << num_p(static_cast<int>(rhs.articles.size()));
	for(Article a : rhs.articles) {
		out << num_p(a.first);
		out << string_p(a.second);
	}
	out << protocol::Protocol::COM_END;
	return out;
}

#endif /* end of include guard: ANS_LIST_ART_H__ */