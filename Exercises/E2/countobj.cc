/*
 * countobj.cc: count creation and destruction of objects.
 */

#include <iostream>
#include <string>

class Counted {
public:
    Counted();
    Counted(const Counted&);
    Counted& operator=(const Counted&);
    ~Counted();
    static int getNbrObj();
private:
    static int nbrObj;
};

int Counted::nbrObj = 0;

Counted::Counted() {
    nbrObj++;
}

Counted::Counted(const Counted& ref) {
    nbrObj++;
}

Counted& Counted::operator=(const Counted& ref){
    return *this;
}

Counted::~Counted() {
    nbrObj--;
}

int Counted::getNbrObj() {
    return nbrObj;
}

void f() {
    Counted c;
    Counted* pc = new Counted;
    delete pc;
}

void g() {
    Counted c1;
    Counted c2 = c1;
}

void h() {
    Counted c1;
    Counted c2;
    c2 = c1;
}

void printNbrObjects(const std::string& msg) {
    std::cout << msg << " -- number of objects: "
              << Counted::getNbrObj() << std::endl;
}
   
int main() {
    using namespace std;
    
    printNbrObjects("Program start, before f()");
    f();

    printNbrObjects("After f(), before g()    ");
    g();

    printNbrObjects("After g(), before h()    ");
    h();

    printNbrObjects("After h(), program end   ");
}
