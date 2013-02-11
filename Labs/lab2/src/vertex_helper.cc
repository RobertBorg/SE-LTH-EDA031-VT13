#include "vertex_helper.h"
#include "vertex.h"

std::ostream& operator<<(std::ostream& os, const Vertex& obj) {
	for(auto itt = obj.dependencies.begin(); itt != obj.dependencies.end(); ++itt){
		os << **itt;
	}
	os << obj.name;
	return os;
} 
