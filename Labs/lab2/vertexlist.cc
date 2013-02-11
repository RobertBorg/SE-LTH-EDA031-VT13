#include <string>
#include <iostream>
#include "vertexlist.h"
#include "vertex.h"

namespace cpp_lab2 {
    VertexList::VertexList() {
        //
        // *** IMPLEMENT ***
        //
    }
    
    VertexList::~VertexList() {
        //
        // *** IMPLEMENT ***
        //
    }
    
    void VertexList::add_vertex(const std::string& name) {
        //
        // *** IMPLEMENT ***
        //
    }   
    
    void VertexList::add_arc(const std::string& from, const std::string& to) {
        //
        // *** IMPLEMENT ***
        //
    }
    
    std::stack<std::string> VertexList::top_sort() throw(cyclic) {
        std::stack<std::string> result;
        //
        // *** IMPLEMENT ***
        //        
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

    void VertexList::insert(Vertex* v) {
        //
        // *** IMPLEMENT ***
        //
    }
    
    Vertex* VertexList::find(const std::string& name) const {
        //
        // *** IMPLEMENT ***
        //
        return 0;
    }
    
    void VertexList::dfs_visit(Vertex* v, std::stack<std::string>& result) throw(cyclic) {
        //
        // *** IMPLEMENT ***
        //
    }
}
