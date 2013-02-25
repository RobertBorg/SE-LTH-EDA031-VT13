#include <iostream>
#include "fibonacci.h"

using namespace std;

int main() {
    Fibonacci fibGenerator;
    cout << "Type a number: ";
    int n;
    while (cin >> n) {
        cout << "fibonacci(" << n << ") is " 
        << fibGenerator.fibonacci(n) << endl;
        cout << "Type another number: ";
    }
}
