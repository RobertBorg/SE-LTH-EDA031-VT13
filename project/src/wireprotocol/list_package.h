#ifndef LIST_PACKAGE_H__
#define LIST_PACKAGE_H__


class ComListPackage : public ComPackage{
public:
	AnsPackage process(Database *db){
		// go through database and list EVERYTHING
	}
};

istream_news& operator>>(istream_news &in, ComListPackage &rhs) {


}



#endif