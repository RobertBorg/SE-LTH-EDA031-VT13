#ifndef VERTEX_H__
#define VERTEX_H__

#include <set>
#include <string>
#include <boost/shared_ptr.hpp>

using std::set;
using boost::shared_ptr;
using std::string;

class Vertex {
	friend std::ostream& operator<<(std::ostream& os, Vertex& obj);
public:
	bool isRootVertex;
	Vertex(const string& inName ) : isRootVertex(true), name(inName), visited(false) {}

	void addDependency(shared_ptr<Vertex> dep ) {
		dependencies.insert(dep);
	}

private:
	string name;
	bool visited;
	set< shared_ptr<Vertex> > dependencies;
};

#endif /* end of include guard: VERTEX_H__ */