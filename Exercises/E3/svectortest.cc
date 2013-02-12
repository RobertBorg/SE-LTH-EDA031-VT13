/*
 * svectortest.cc
 */
 
#include <iostream>
#include "svector.h"

using namespace std;

/*
 * A function that prints all the elements in the SVector sv 
 */
void print(SVector sv) {
    int size = sv.size();
    for (int i = 0; i < size; ++i)
        cout << sv.get(i) << " ";
}

int main() {
    const int V1SIZE = 10;
    SVector v1(V1SIZE);
    for (int i = 0; i < V1SIZE; ++i)
        v1.set(i, i+1);
    
    print(v1);             // should print 1 2 3 4 5 6 7 8 9 10
    cout << endl;
    
    const int V2SIZE = 5;
    SVector v2(V2SIZE);
    for (int i = 0; i < V2SIZE; ++i)
        v2.set(i, 10*(i+1));
    print(v2);             // should print 10 20 30 40 50
    cout << endl;
    
    print(v1);             // should print 1 2 3 4 5 6 7 8 9 10
    cout << endl;
}
