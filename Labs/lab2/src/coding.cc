#include "coding.h"
#include <iostream>
#include <fstream>

char Coding::encode(char& c){
	return c ^ 0x80;
}

char Coding::decode(char& c){
	return c ^ 0x80;
}
using namespace std;
int Coding::process(char(*processChar)(char& in), int argc, const char* argv[]) {
	istream* myInput;
	if(argc != 2){
		myInput = &cin;
	} else {
		myInput = new ifstream;
		static_cast<ifstream*>(myInput)->open(argv[1]);
		if(!static_cast<ifstream*>(myInput)->is_open()){
			delete myInput;
			return -1;
		}
	}

	char c;
	if(!myInput->eof()){
		myInput->get(c);
		do{
			cout.put(processChar(c));
			myInput->get(c);	
		} while(!myInput->eof());
	}
	cout << flush;
	if(argc == 2){
		static_cast<ifstream*>(myInput)->close();
		delete myInput;
	}
	return 0;
}
