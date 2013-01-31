/*
 * list.cc
 */

#include <limits>
#include "list.h"
#include "debug.h"

/*
 * See debug.h for information on assert() and TRACE. Examples of use
 * are in the List destructor. Insert similar calls in other functions,
 * if you need them.
 *
 */

namespace cpp_lab1 {
    
    List::Node::Node(long v, Node* n) : value(v), next(n) {}
    
    List::List() : head(new Node) {}
    
    List::~List() {
        TRACE("List::~List()");
        assert(head != 0);
        //
        // *** IMPLEMENT ***
        //
    }
    
    void List::insert(long d) {
        //
        // *** IMPLEMENT ***
        //
    }
    
    void List::remove(long d, DeleteFlag df) {
        //
        // *** IMPLEMENT ***
        //
    }
    
    int List::size() const {
        int size = 0;
        //
        // *** IMPLEMENT ***
        //
        return size;
    }
    
    bool List::empty() const {
        bool empty = false;
        //
        // *** IMPLEMENT ***
        //
        return empty;
    }
    
    long List::largest() const {
        long largest = std::numeric_limits<long>::min();
        //
        // *** IMPLEMENT ***
        //
        return largest;
    }
    
    void List::debugPrint() const {
#ifndef NDEBUG
        //-----------------------------------------------------------------
        // debugPrint() is used only during development, so we enclose the
        // code in this #ifndef block. The code will be removed when NDEBUG 
        // is defined.
        //
        // NDEBUG should be defined when compiling production release
        // versions. Use the -DNDEBUG option on the compiler command line.
        //-----------------------------------------------------------------
        for (Node* iter = head->next; iter != 0; iter = iter->next) {
            std::cout << iter->value << " ";
        }
        std::cout << std::endl;
#endif
    }
}

