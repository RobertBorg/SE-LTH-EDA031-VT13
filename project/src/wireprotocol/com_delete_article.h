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


istream_news& operator>>(istream_news &in, ComDeleteArticlePacket &rhs) {
	in.eat(Protocol::COM_LIST_ART);
	num_p num;
	in >> num;
	groupNum = num;
	in >> num;
	articNum = num;
	in.eat(Protocol::COM_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, ComDeleteArticlePacket &rhs) {
	out << Protocol::COM_LIST_ART;
	out << num_p(groupNum);
	out << num_p(articNum);
	out << Protocol::COM_END;
	return out;
}

#endif