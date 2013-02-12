/*
 * shapetest.cc: create three objects, check their type.
 */

#include <iostream>

using namespace std;

/*
 * A base class Shape with two derived classes Square and Circle.
 */
class Shape {
public:
    virtual void print() const { cout << "I'm a Shape" << endl; }
};

class Square : public Shape {
public:
    virtual void print() const { cout << "I'm a Square" << endl; }
};

class Circle : public Shape {
public:
    virtual void print() const { cout << "I'm a Circle" << endl; }
};

int main() {
    /*
     * Create three objects.
     */
    Shape aShape;
    Square aSquare;
    Circle aCircle;
    
    /*
     * Call print() in each object to check the kind of object.
     * The output should be I'm a Shape / Square / Circle
     */
    aShape.print();
    aSquare.print();
    aCircle.print();
    
    /*
     * Call print() on the same objects via a Shape* pointer. 
     * The output should be the same as above, but becomes
     * Shape / Shape / Shape instead.
     */
    Shape* psh = &aShape;
    Shape* psq = &aSquare;
    Shape* pci = &aCircle;
    psh->print();
    psq->print();
    pci->print();
}
