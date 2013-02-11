#include "vertex_helper.h"
#include "vertex.h"
#include "make.h"


std::ostream& operator<<(std::ostream& os, Vertex& obj) {
	if(obj.visited) {
		return os;
	}
	obj.visited=true;
	for(auto itt = obj.dependencies.begin(); itt != obj.dependencies.end(); ++itt){
		os << *((*itt).lock());

	}
	os << obj.name;
	return os;
} 
