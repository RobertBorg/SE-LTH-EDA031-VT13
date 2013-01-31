#include "coding.h"

char Coding::encode(char& c){
	return c ^ 0x80;
}

char Coding::decode(char& c){
	return c ^ 0x80;
}