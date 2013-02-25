#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cout;
using std::endl;
#include "date.h"
using cpp_lab3::Date;

template<typename T>
string toString(T in) {
	stringstream tmp;
	tmp << in;
	return tmp.str();
}

struct StringCastException {
	StringCastException (const string& inWhat) : what(inWhat) {}
	string what;
};

template<typename T>
T string_cast(const string& in) {
	stringstream ss(in);
	T tmp;
	ss >> tmp;
	if(!ss) {
		StringCastException e(in);
		throw e;
	}
	return tmp;
}

int main (int argc, char* argv[]) {
	double d = 1.234;
	Date today;
	std::string sd = toString(d);
	std::string st = toString(today);

	//cout << sd << endl;
	//cout << st << endl;

	try {
		int i = string_cast<int>("123");
		cout << i << endl;
		double d = string_cast<double>("12.34");
		cout << d << endl;
		Date date = string_cast<Date>("2011-01-10");
		cout << date << endl;
		double dd = string_cast<double>("asd");
		cout << dd << endl;
	} catch (StringCastException& e) {
		cout << "... error unable to parse:\""  << e.what << '\"' << endl;
	}
	return 0;
}