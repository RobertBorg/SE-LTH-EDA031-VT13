#include "make.h"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	Make m;
	if(argc == 2){
		m.readfile(argv[1]);
	} else {
		m.readfile("test1.txt");
	}
	try {
		m.printCompileOrder(); 
	} catch (cyclic& e) {
		cout << e.what() << endl;
	}
	return 0;
}