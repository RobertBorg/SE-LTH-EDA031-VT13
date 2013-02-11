/*
 * Explain the output of the following program. Also correct
 * the error in the program (it is an error that you would 
 * never notice, but it's still an error).
 */

#include <iostream>
#include "date.h"

using namespace std;

int main() {
    Date d;
    cout << "sizeof(d)  = " << sizeof(d) << endl; // 3 * 4 bytes
    
    Date* pd = new Date;
    cout << "sizeof(pd) = " << sizeof(pd) << endl; // 4 bytes

    delete pd;
}
