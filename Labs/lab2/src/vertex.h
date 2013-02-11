#ifndef VERTEX_H__
#define VERTEX_H__

#include <set>
#include <string>
#include <boost/shared_ptr.hpp>

using std::set;
using boost::shared_ptr;
using std::string;

class Vertex {
	friend std::ostream& operator<<(std::ostream& os, const Vertex& obj);
public:
	Vertex(const string& inName ) : name(inName) {}

	void addDependency(shared_ptr<Vertex> dep ) {
		dependencies.insert(dep);
	}
private:
	string name;
	set< shared_ptr<Vertex> > dependencies;
};

#endif /* end of include guard: VERTEX_H__ */