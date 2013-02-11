#ifndef MAKE_H__
#define MAKE_H__

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include "file_handle.h"
#include "vertex.h"
#include "vertex_helper.h"
#include <exception>


using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using boost::shared_ptr;


class cyclic: public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Cyclic dependency detected!";
	}
};

class Make {
public: 
	typedef map<string, shared_ptr<Vertex> > MakeMap; 
	typedef shared_ptr<Vertex> VertexPtr;
	typedef set<VertexPtr> VertexSet;
	void readfile(const string filename) {
		string input;
		FileHandle file(filename);
		(*file) >> input;
		if(!(*file).eof()) {
			do {
				handleInput(input);
				(*file) >> input;
			} while (!(*file).eof());
		}

	}

	void printCompileOrder() {
		for( auto itt = globalVertexMap.begin(); itt != globalVertexMap.end(); ++itt) {
			auto node =(*itt).second;
			if(node->isRootVertex) {
				rootTargets.insert(node);
			}
		}
		if(rootTargets.empty()) {
			cyclic e;
			throw e;
		}
		for( auto itt = rootTargets.begin(); itt != rootTargets.end(); ++itt) {
			cout << **itt << endl;
		}
	}

private:
	MakeMap globalVertexMap;
	VertexSet rootTargets;
	shared_ptr<Vertex> currentNode;
	shared_ptr<Vertex> getPutFromGlobal(const string& name) {
		 auto mapItt = globalVertexMap.find(name);
		if( mapItt != globalVertexMap.end() ){
			shared_ptr<Vertex> toRtn = (*mapItt).second;
			return toRtn;
		} else {
			shared_ptr<Vertex> toInsert(new Vertex(name));
			globalVertexMap[name] = toInsert;
			return toInsert;
		}

	}
	void handleInput(const string& input){
		size_t colonPos = input.find(':');
		if( colonPos == string::npos) {
			if(currentNode.get() != nullptr) {
				VertexPtr node = getPutFromGlobal(input);
				currentNode->addDependency(node);
				node->isRootVertex=false;
			}
		} else {
			currentNode = getPutFromGlobal(input.substr(0,colonPos));
		}
	}
};

#endif /* end of include guard: MAKE_H */