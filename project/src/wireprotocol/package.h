#ifndef PACKAGE_H__
#define PACKAGE_H__

/* Abstract superclass for packages */



class ComPackage {
public:
	virtual shared_ptr<AnsPackage> process(Database *db) const;


};

class AnsPackage {
public:
	virtual void process() const;


};


#endif