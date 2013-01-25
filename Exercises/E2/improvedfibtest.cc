#include <iostream>
#include "improvedfibonacci.h"
#include <stdexcept>

using namespace std;

int main() {
    ImprovedFibonacci fibGenerator;
    cout << "Type a number: ";
    int n;
    while (cin >> n) {
	try {
		cout << "fibonacci(" << n << ") is " 
		<< fibGenerator.fibonacci(n) << endl;
	} catch ( std::out_of_range& e) {
		cout << e.what() << endl;	
	}
	cout << "Type another number: ";
    }
}
