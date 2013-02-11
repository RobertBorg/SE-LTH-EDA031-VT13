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

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using boost::shared_ptr;

class Make {
public: 
	typedef map<string, shared_ptr<Vertex> > MakeMap; 
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
			cout << *(*itt).second << endl;
		}
	}
private:
	MakeMap globalVertexMap;
	shared_ptr<Vertex> currentNode;
	shared_ptr<Vertex> getPutFromGlobal(const string& name, bool remove) {
		 auto mapItt = globalVertexMap.find(name);
		if( mapItt != globalVertexMap.end() ){
			shared_ptr<Vertex> toRtn = (*mapItt).second;
			if( remove) {
				globalVertexMap.erase(mapItt);
			}
			return toRtn;
		} else {
			shared_ptr<Vertex> toInsert(new Vertex(name));
			if(!remove) {
				globalVertexMap[name] = toInsert;
			}
			return toInsert;
		}

	}
	void handleInput(const string& input){
		size_t colonPos = input.find(':');
		if( colonPos == string::npos) {
			if(currentNode.get() != nullptr) {
				currentNode->addDependency(getPutFromGlobal(input,true));
			}
		} else {
			currentNode = getPutFromGlobal(input.substr(0,colonPos),false);
		}
	}
};

#endif /* end of include guard: MAKE_H */