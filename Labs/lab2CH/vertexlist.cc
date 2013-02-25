#include <string>
#include <iostream>
#include "vertexlist.h"
#include "vertex.h"

namespace cpp_lab2 {
    VertexList::VertexList() {

    }
    
    VertexList::~VertexList() {
        
    }
    
    void VertexList::add_vertex(const std::string& name) {
        Vertex *toAdd = new Vertex(name);
        vptrs.push_back(toAdd);
    }   
    
    void VertexList::add_arc(const std::string& from, const std::string& to) {
        Vertex *arc = find(from);
        if(arc != 0) {
            Vertex *toAdd = find(to);
            if(toAdd != 0) {
                arc->adj.insert(toAdd);
            } 
        }
    }
    
    std::stack<std::string> VertexList::top_sort() throw(cyclic) {
        std::stack<std::string> result;
        /* 1. initialize the graph and the result stack */
        for(std::vector<Vertex*>::iterator w = vptrs.begin(); w != vptrs.end(); ++w) {
            (*w)->color = Vertex::WHITE;
        }
        /* 2. search from all unvisited vertices */
        for(std::vector<Vertex*>::iterator w = vptrs.begin(); w != vptrs.end(); ++w) {
            int color = (*w)->color;
            int white = Vertex::WHITE;
            if (color == white)
                dfs_visit(*w, result);
        }
        return result;
    }


    
    void VertexList::debugPrint() const {
        using namespace std;
        cout << "VertexList, n = " << vptrs.size() << endl;
        for (size_t i = 0; i < vptrs.size(); ++i) {
            Vertex* v = vptrs[i];
            cout << "Vertex " << v->name << ". Adjacent: ";
            VertexList& vl = v->adj;
            for (size_t j = 0; j < vl.vptrs.size(); ++j)
                cout << vl.vptrs[j]->name << " ";
            cout << endl;
        }
    }


    /*
    *   insert the vertex pointer v in vptrs, if it's not already there
    */
    void VertexList::insert(Vertex* v) {
        for(std::vector<Vertex*>::iterator w = vptrs.begin(); w != vptrs.end(); ++w) {
            if(v == (*w))
                return;
        }
        vptrs.push_back(v);
    }

    /*
    *   return a pointer to the vertex named name, 0 if not found
    */    
    Vertex* VertexList::find(const std::string& name) const {

        for(std::vector<Vertex*>::const_iterator w = vptrs.begin(); w != vptrs.end(); ++w) {
            if((*w)->name == name) {
                return *w;
            }
        }
        return 0;
    }


    
    /*
    *   visit v in the traversal algorithm
    */
    void VertexList::dfs_visit(Vertex* v, std::stack<std::string>& result) throw(cyclic) {
        /* 1. white vertex v is just discovered, color it gray */
        int vColor = v->color;
        int gray = Vertex::GRAY;
        if(vColor == gray) {
            throw cyclic();
        } else if(v->color == Vertex::BLACK) {
            return;
        }
       // std::cout << v->color << std::endl;
        v->color = Vertex::GRAY;
       // std::cout << v->color << std::endl;
        /* 2. recursively visit all unvisited adjacent nodes */
        for(std::vector<Vertex*>::iterator w = v->adj.vptrs.begin(); w != v->adj.vptrs.end(); ++w) {
            if((*w)->color == Vertex::WHITE) {
                dfs_visit(*w, result);
            }
        }
        /* 3. finish vertex v (color it black and output it) */
        v->color = Vertex::BLACK;
        result.push(v->name);
    }
}
