#include "sieveoferatosthenes.h"
#include <iostream>

using std::cout;
using std::endl;
int main (int argc, char* argv[]){
	SieveOfEratosthenes soe10;
	cout << soe10.doAlgo() << endl;
	SieveOfEratosthenes soe100k(100000);
	size_t lastPrime = soe100k.doAlgo().rfind('P');
	cout << lastPrime << endl;
	return 0;
}