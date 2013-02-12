/* 
 * Class SVector: an integer vector class with basic functionality
 * (get and set operations).
 */

#ifndef SVECTOR_H
#define SVECTOR_H

#include <cstdlib>
#include <algorithm>

using std::copy;

class SVector {
public:
    explicit SVector(size_t size); // a vector with 'size' elements
    SVector(const SVector& other) : n(other.n) {
    	v = new int[n];
    	copy(other.v, other.v +n,v);
    }
    SVector& operator=(const SVector& other){
		if (this != &other) {
			delete [] v;
    		
    		n = other.n;
    		copy(other.v, other.v +n,v);	
		}
		return *this;
    }
    ~SVector();                    // deallocate the vector
    int size() const;              // get the number of elements
    int get(int i) const;          // get the number at index i
    void set(int i, int value);    // change the number at index i
private:
    int* v;    // an array to hold the numbers
    size_t n;  // the size of the array
};

#endif
