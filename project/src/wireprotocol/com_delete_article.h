#ifndef COM_DELETE_ARTICLE_H__
#define COM_DELETE_ARTICLE_H__

#include <string>

using std::string;

class ComDeleteArticlePacket : public ComPacket{
public:
	AnsPacket process(Database *db){
		
	}
	ComDeleteArticlePacket() = default;
	ComDeleteArticlePacket(int groupNum_, int articNum_): groupNum(groupNum_), articNum(articNum_){}


private:
	int groupNum;
	int articNum;
};


Connection& operator>>(Connection &inConn, ComDeleteArticlePacket &rhs) {
	eat(protocol::COM_LIST_ART);
	num_p num;
	inConn >> num;
	groupNum = num;
	inConn >> num;
	articNum = num;
	eat(protocol::COM_END);
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