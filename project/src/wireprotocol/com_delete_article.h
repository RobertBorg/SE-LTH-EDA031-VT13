#ifndef COM_DELETE_ARTICLE_H__
#define COM_DELETE_ARTICLE_H__

#include <string>

using std::string;

class ComDeleteArticlePacket : public ComPacket{
public:
	AnsPacket process(Database& db){
		try{
			db->deleteArticle(articNum, groupNum);
		}catch (NGDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket(AnsDeleteArticlePacket::createNGNotFound());
			return answerPacket;
		} catch (ArtDoesntExistException e){
			shared_ptr<AnsPacket> answerPacket(AnsDeleteArticlePacket::createArtNotFound());
			return answerPacket;
		}
	}
	ComDeleteArticlePacket() = default;
	ComDeleteArticlePacket(uint32_t groupNum_, uint32_t articNum_): groupNum(groupNum_), articNum(articNum_){}


private:
	uint32_t groupNum;
	uint32_t articNum;
};


Connection& operator>>(Connection &inConn, ComDeleteArticlePacket &rhs) {
	Packet::eat(in, protocol::COM_LIST_ART);
	num_p num;
	inConn >> num;
	groupNum = num;
	inConn >> num;
	articNum = num;
	Packet::eat(in, protocol::COM_END);
	return inConn;
}

Connection& operator<<(Connection &outConn, ComDeleteArticlePacket &rhs) {
	outConn << protocol::COM_LIST_ART;
	outConn << num_p(groupNum);
	outConn << num_p(articNum);
	outConn << protocol::COM_END;
	return outConn;
}

#endif