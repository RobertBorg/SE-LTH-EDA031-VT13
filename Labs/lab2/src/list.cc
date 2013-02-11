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
        
        Node* c = head; 
        while(c != 0) {
            Node* toDelete = c;
            c=c->next;
            delete toDelete;
        }
    }
    
    void List::insert(long d) {
        Node* tmp = new Node(d,head->next);
        head->next = tmp;
    }
    
    void List::remove(long d, DeleteFlag df) {
        Node* p = 0;
        Node* c = head;
        bool terminateSearch = false;
        while(!terminateSearch && c->next != 0 ){
            p = c;
            c=c->next;
            switch(df){
                case List::LESS:
                    if(c->value < d){
                        terminateSearch = true;
                    }
                break;
                case List::EQUAL:
                    if(c->value == d){
                        terminateSearch = true;
                    }
                break;
                case List::GREATER:
                    if(c->value > d){
                        terminateSearch = true;
                    }
                break;
            }
        }

        if(terminateSearch){
            p->next = c->next;
            delete c;
        }
    }
    
    int List::size() const {
        int size = 0;
        Node* c = head;
        while(c->next != 0){
            c=c->next;
            size++;
        }
        return size;
    }
    
    bool List::empty() const {
        return head->next == 0;
    }
    
    long List::largest() const {
        long largest = std::numeric_limits<long>::min();
        Node* c = head;
        while(c->next != 0){
            c=c->next;
            if(c->value > largest){
                largest = c->value;
            }
        }
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

