#ifndef COM_DELETE_ARTICLE_H__
#define COM_DELETE_ARTICLE_H__

#include <string>

using std::string;
template <typename Database>
class ComDeleteArticlePacket : public ComPacket<Database>{
friend Connection& operator>>(Connection &in, ComDeleteArticlePacket &rhs);
friend Connection& operator<<(Connection &out, ComDeleteArticlePacket &rhs);
public:
	shared_ptr<AnsPacket> process(Database& db){
		try{
			db->deleteArticle(articNum, groupNum);
			shared_ptr<AnsPacket> answerPacket = AnsDeleteArticlePacket::createSuccessful();
			return answerPacket;
		}catch (NGDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket = AnsDeleteArticlePacket::createNGNotFound();
			return answerPacket;
		} catch (ArtDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket = AnsDeleteArticlePacket::createArtNotFound();
			return answerPacket;
		}
	}
	ComDeleteArticlePacket() = default;
	ComDeleteArticlePacket(uint32_t groupNum_, uint32_t articNum_): groupNum(groupNum_), articNum(articNum_){}


private:
	uint32_t groupNum;
	uint32_t articNum;
};

template <typename Database>
Connection& operator>>(Connection &inConn, ComDeleteArticlePacket<Database> &rhs) {
	Packet::eat(inConn, protocol::Protocol::COM_LIST_ART);
	num_p num;
	inConn >> num;
	rhs.groupNum = num;
	inConn >> num;
	rhs.articNum = num;
	Packet::eat(inConn, protocol::Protocol::COM_END);
	return inConn;
}

template <typename Database>
Connection& operator<<(Connection &outConn, ComDeleteArticlePacket<Database> &rhs) {
	outConn << protocol::Protocol::COM_LIST_ART;
	outConn << num_p(rhs.groupNum);
	outConn << num_p(rhs.articNum);
	outConn << protocol::Protocol::COM_END;
	return outConn;
}

#endif