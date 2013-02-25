#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <cstdlib>
#include "graph.h"

using namespace cpp_lab2;
using namespace std;

struct parse_error {};
            
void buildGraph(Graph& g, std::istream& infile) throw(parse_error, cyclic) {
    //
    // *** IMPLEMENT ***
    //    
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: topsort infile" << endl;
        exit(1);
    }
    ifstream infile(argv[1]);
    if (! infile) {
        cerr << "Cannot open " << argv[1] << endl;
        exit(1);
    }
    
    try {
        Graph g;
        cout << "Building graph ..." << flush;
        buildGraph(g, infile);
        cout << " done." << endl;
        
        cout << "Computing topological order ..." << flush;
        stack<string> order = g.top_sort();
        cout << " done." << endl;
        
        cout << "A topological order is:" << endl;
        cout << "   ";
        while (! order.empty()) {
            cout << order.top() << " ";
            order.pop();
        }
        cout << endl;
    }
    catch (parse_error&) {
        cerr << endl << "Syntax error in the infile" << endl;
    }
    catch (cyclic&) {
        cerr << endl << "The graph is cyclic" << endl;
    }
    
    infile.close();
}
