#ifndef STRING_P_H__
#define STRING_P_H__

#include "num_p.h"

#include <string>
using std::string;
#include "../../lib/clientserver/connection.h"
using client_server::Connection;

struct string_p : public Packet{
	string value;
	string_p() {}
	string_p(const string &in) : value(in) {}
	const operator string() {
		return value;
	}

	string_p &operator=(std::string str){
		this->value = str;
		return *this;
	}
};


template <typename istream>
istream &operator>>(istream &in, string_p &rhs) {
	Packet::eat(in, protocol::Protocol::PAR_STRING);
	num_p size;
	in >> size;
	char c;
	while(size.value-- > 0) {
		in >> c;
		rhs.value.push_back(c);
	}
	return in;
}

template <typename ostream>
ostream &operator<<(ostream &out, const string_p &rhs) {
	out << protocol::Protocol::PAR_STRING;
	num_p size(rhs.value.length());
	out << size;
	for(auto i = rhs.value.begin(); i != rhs.value.end(); ++i) {
		out << *i;
	}
	return out;
}

#endif /* end of include guard: STRING_P_H__ */
