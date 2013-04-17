#ifndef SERVER_OPTIONS_H__
#define SERVER_OPTIONS_H__

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <boost/program_options.hpp>
#include "../lib/clientserver/server.h"

using namespace boost::program_options;

class ServerOptions : private variables_map {
public:
	using variables_map::operator[];
	using variables_map::count;
	ServerOptions(int argc, char* argv[]) : cmdDesc("Allowed options") {
		cmdDesc.add_options()
			("help", "produce help message")
			("server-port",value<uint16_t>() ,"liston on port arg")
			("persistent-db", value<bool>(), "persistent database on disk [true/false]");
		
		

		store(command_line_parser(argc, argv).options(cmdDesc).run(), *this);
		notify();
	}
	ServerOptions& operator() () {
		if(count("help") || !count("server-port") || !count("persistent-db")) {
			cout << 
			"Usage:" << endl <<
			"newsserver [options] " << endl;
			cout << cmdDesc << endl;
		}
		return *this;
	}
private:
	options_description cmdDesc;
};

#endif /* end of include guard: OPTIONS_H__ */
