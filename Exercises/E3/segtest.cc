/*
 * segtest.cc: tests so class Segment exhibits correct value semantics.
 */

#include <iostream>
#include "segment.h"

using namespace std;

int main() {
    Segment s1(1, 1, 2, 2);
    cout << "Length of s1 is: " << s1.getLength() << endl; // 1.414
    cout << endl;
    
    Segment s2 = s1;
    s1.setToOrigo();
    cout << "Length of s1 is: " << s1.getLength() << endl; // 0 now
    cout << "Length of s2 is: " << s2.getLength() << endl; // 1.414
    cout << endl;
    
    Segment s3(0, 0, 0, 0);
    s3 = s2;
    s2.setToOrigo();
    cout << "Length of s1 is: " << s1.getLength() << endl; // 0 still
    cout << "Length of s2 is: " << s2.getLength() << endl; // 0 now
    cout << "Length of s3 is: " << s3.getLength() << endl; // 1.414
}
