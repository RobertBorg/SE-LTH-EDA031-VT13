#ifndef COM_DELETE_ARTICLE_H__
#define COM_DELETE_ARTICLE_H__

#include <string>

using std::string;


template <typename Database, typename istream = Connection, typename ostream = Connection>
class ComDeleteArticlePacket : public ComPacket<Database, istream, ostream> {
friend istream& operator>>(istream &in, ComDeleteArticlePacket<Database, istream, ostream> &rhs) {
	Packet::eat(in, protocol::Protocol::COM_LIST_ART);
	num_p num;
	in >> num;
	rhs.groupNum = num;
	in >> num;
	rhs.articNum = num;
	Packet::eat(in, protocol::Protocol::COM_END);
	return in;
}
friend ostream& operator<<(ostream &out, ComDeleteArticlePacket<Database, istream, ostream> &rhs) {
	out << protocol::Protocol::COM_LIST_ART;
	out << num_p(rhs.groupNum);
	out << num_p(rhs.articNum);
	out << protocol::Protocol::COM_END;
	return out;
}
public:
	virtual shared_ptr<AnsPacket<istream, ostream>> process(Database& db) const{
		try{
			db.deleteArticle(articNum, groupNum);
			shared_ptr<AnsPacket<istream, ostream>> answerPacket = AnsDeleteArticlePacket<istream, ostream>::createSuccessful();
			return answerPacket;
		}catch (NGDoesntExistException e){
			shared_ptr<AnsPacket<istream, ostream>> answerPacket = AnsDeleteArticlePacket<istream, ostream>::createNGNotFound();
			return answerPacket;
		} catch (ArtDoesntExistException e){
			shared_ptr<AnsPacket<istream, ostream>> answerPacket = AnsDeleteArticlePacket<istream, ostream>::createArtNotFound();
			return answerPacket;
		}
	}
	ComDeleteArticlePacket() = default;
	ComDeleteArticlePacket(uint32_t groupNum_, uint32_t articNum_): groupNum(groupNum_), articNum(articNum_){}
	virtual void write(ostream &out) {
		out << *this;
	}

	virtual void read(istream &in) {
		in >> *this;
	}

private:
	uint32_t groupNum;
	uint32_t articNum;
};

#endif