#ifndef STRING_P_H__
#define STRING_P_H__


#include "iostream_news.h"
#include "num_p.h"

#include <string>
using std::string;

struct string_p {
	string value;
};

iostream_news &operator>>(iostream_news &in, string_p &rhs) {
	num_p size;
	in >> size;
	char c;
	while(size.value-- > 0) {
		in >> c;
		rhs.value.push_back(c);
	}
	return in;
}

iostream_news &operator<<(iostream_news &out, string_p &rhs) {
	num_p size(rhs.value.length());
	out << size;
	for(auto i = rhs.value.begin(); i != rhs.value.end(); ++i) {
		out << *i;
	}
	return out;
}

#endif /* end of include guard: STRING_P_H__ */