/*
 * memtest.cc: a program to demonstrate what happens when objects are 
 * allocated in different ways. Also shows what happens when objects 
 * are used as parameters. One class and several functions are used; 
 * these are all in this file.
 */

#include <iostream>
#include <string>

/* 
* The class A contains a string 'id', a constructor, and a function
 * to return the value of 'id'. In addition, there is a destructor, 
 * a copy constructor, and an overloaded assignment operator. These 
 * are not necessary for the class to function correctly -- they have 
 * been introduced so we can follow what happens when objects are
 * created, copied and destroyed.
 */
class A {
public:
    explicit A(const std::string& id); // A("the id")
    ~A();                              // destructor
    A(const A& a);                     // copy constructor
    A& operator=(const A& a);          // assignment operator
    std::string getId() const;         // returns the id
private:
    std::string id;
};

/* 
 * Implementation of the class A: just print messages so we can see when 
 * each function is called.
 */

using namespace std;

A::A(const string& id) {
    this->id = id;
    cout << "A(" << id << ")" << endl;
}

A::~A() {
    cout << "~A(), id = " << id << endl;
}

A::A(const A& a) {
    id = a.id + " copy";    // in a "normal" copy constructor, this would 
                            // be id = a.id;
    cout << "A copy, id = " << id << endl;
}

A& A::operator=(const A& a) {
    id = a.id + " assigned"; // in a "normal" assignment, this would 
                             // be id = a.id
    cout << "A assign, id = " << id << endl;
    return *this;
}

string A::getId() const {
    return id;
}

/*
 * The functions f1-f5 demonstrate different usages of objects.
 */

/*
 * f1: create a local (stack-allocated) object.
 */
void f1() {
    cout << "Entering f1()" << endl;
    A local("f1local");
    cout << "Leaving f1()" << endl;
}

/*
 * f2: object as a parameter, passed by value.
 */
void f2(A a) {
    cout << "Entering f2(A a)" << endl;
    cout << "a.id = " << a.getId() << endl;
    cout << "Leaving f2(A a)" << endl;
}

/*
 * f3: object as parameter, passed by constant reference.
 */
void f3(const A& a) {
    cout << "Entering f3(const A& a)" << endl;
    cout << "a.id = " << a.getId() << endl;
    cout << "Leaving f3(const A& a)" << endl;
}

/*
 * f4: pointer to object as parameter.
 */
void f4(A* pa) {
    cout << "Entering f4(A* pa)" << endl;
    cout << "pa->id = " << pa->getId() << endl;
    cout << "Leaving f4(A* pa)" << endl;
}

/*
 * f5: creates and returns a heap-allocated object.
 */
A* f5() {
    cout << "Entering f5()" << endl;
    A* pa = new A("f5heap");
    cout << "Leaving f5()" << endl;
    return pa;
}

/*
 * A global object, created before main() starts and destructed after
 * main() finishes.
 */
A global("global");

/* 
* main(): create objects in different ways, call f1-f5.
 */
int main() {
    cout << "---> main(), entering" << endl;
    cout << endl;
    
    cout << "---> main(), create mainlocal" << endl;
    A mainlocal("mainlocal");
    cout << endl;
	
    cout << "---> main(), copy mainlocal" << endl;
    A copy = mainlocal;
    cout << endl;
	
    cout << "---> main(), assign mainlocal" << endl;
    copy = mainlocal;
    cout << endl;
	
    cout << "---> main(), call f1()" << endl;
    f1();
    cout << endl;
	
    cout << "---> main(), call f2(mainlocal)" << endl;
    f2(mainlocal);
    cout << endl;
	
    cout << "---> main(), call f3(mainlocal)" << endl;
    f3(mainlocal);
    cout << endl;
	
    cout << "---> main(), create mainheap" << endl;
    A* mainheap = new A("mainheap");
    cout << endl;
	
    cout << "---> main(), call f4(mainheap)" << endl;
    f4(mainheap);
    cout << endl;
	
    cout << "---> main(), call f5heap = f5()" << endl;
    A* f5heap = f5();
    cout << endl;
	
    cout << "---> main(), delete mainheap" << endl;
    delete mainheap;
    cout << endl;
	
    cout << "---> main(), delete f5heap" << endl;
    delete f5heap;
    cout << endl;
	
    cout << "---> main(), leaving" << endl;
}
