#ifndef COM_LIST_ARTICLE_H__
#define COM_LIST_ARTICLE_H__


class ComListArticlePackage : public ComPackage{
public:
	AnsPackage process(Database *db){
		
	}
	ComListArticlePackage(int groupNum_): groupNum(groupNum_){}


private:
	int groupNum;
};


istream_news& operator>>(istream_news &in, ComListArticlePackage &rhs) {
	in.eat(Protocol::COM_LIST_ART);
	num_p num;
	in >> num;
	groupNum = num;
	in.eat(Protocol::COM_END);
	return in;
}

iostream_news& operator<<(iostream_news &out, ComListArticlePackage &rhs) {
	out << Protocol::COM_LIST_ART;
	out << num_p(groupNum);
	out << Protocol::COM_END;
	return out;
}



#endif