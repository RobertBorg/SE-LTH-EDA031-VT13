#include "make.h"

int main(int argc, char* argv[]) {
	Make m;
	if(argc == 2){
		m.readfile(argv[1]);
	} else {
		m.readfile("test1.txt");
	}
	m.printCompileOrder(); 
	return 0;
}