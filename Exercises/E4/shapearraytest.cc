/*
 * shapearraytest.cc: check the type of objects that are in 
 * a vector.
 */

#include <iostream>
#include <vector>
#include <cstdlib>  /* for random() */

using namespace std;

/*
 * A base class Shape with two derived classes Square and Circle.
 * With a virtual print() function.
 */
class Shape {
public:
    virtual void print() const { cout << "I'm a Shape" << endl; }
};

class Square : public Shape {
public:
    void print() const { cout << "I'm a Square" << endl; }
};

class Circle : public Shape {
public:
    void print() const { cout << "I'm a Circle" << endl; }
};


int main() {
    /*
     * A vector of Shapes.
     */
    vector<Shape> shapes;
    const size_t NBR_SHAPES = 10;
    
    /*
     * Store 10 squares and circles in the vector.
     */
    for (size_t i = 0; i < NBR_SHAPES; ++i) {
        if (::random() % 2 == 0) {
            Square aSquare;
            shapes.push_back(aSquare);
        }
        else {
            Circle aCircle;
            shapes.push_back(aCircle);
        }
    }
    
    /*
     * Print the shapes.
     */
    for (size_t i = 0; i < shapes.size(); ++i)
        shapes[i].print();
}
