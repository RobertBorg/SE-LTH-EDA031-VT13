#include <iostream>
#include <fstream>
#include "coding.h"

using std::endl;
using std::cout;
using std::ifstream;
using std::cin;
using std::istream;
using std::flush;
using std::cerr;

int main (int argc, const char* argv[]) {
	Coding::process( &Coding::encode,  argc, argv);
}