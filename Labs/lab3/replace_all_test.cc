#include <string>
#include "debug.h"

using std::string;
void replace_all(string& s, const string& from, const string& to){
	size_t pos = s.find(from);
	const size_t fromlen = from.length();
	const size_t tolen = to.length();
	while (pos != string::npos) {
		s.replace(pos,fromlen,to);
		pos = s.find(from,pos+tolen);
	}
}

int main (int argc, char* argv[]){
	string text = "A man, a plan, a canal, Panama!";
	replace_all(text, "an", "XXX");
	assert(text == "A mXXX, a plXXX, a cXXXal, PXXXama!");
	text = "ananan";
	replace_all(text, "an", "XXX");
	assert(text == "XXXXXXXXX");
	text = "ananan";
	replace_all(text, "an", "anan");
	assert(text == "anananananan");
	return 0;
}