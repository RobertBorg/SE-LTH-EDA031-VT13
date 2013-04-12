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
	ServerOptions(int argc, char* argv[]) : cmdDesc("Allowed options"), cmdHiddenDesc("Hidden command line options") {
		cmdDesc.add_options()
			("help", "produce help message"),
			("server-port",value<uint16_t>() ,"produce help message"),
			("persistent-db", "persistent database on disk");

		cmdHiddenDesc.add_options()
			("help", "produce help message"),
			("server-port",value<uint16_t>() ,"produce help message"),
			("persistent-db", value<bool> "persistent database on disk");
		

		store(command_line_parser(argc, argv).options(cmdHiddenDesc).positional(posCmdDesc).run(), *this);
		notify();
	}
	ServerOptions& operator() () {
		if(!count("persistent-db") || count("help")) {
			cout << 
			"Usage:" << endl <<
			"newsreader [options] " << endl <<
			"options:" << endl <<
			"persistent [true/false] - persistent database on disk" << endl;
			

			cout << cmdDesc << endl;
		}
		return *this;
	}
private:
	options_description cmdDesc;
	options_description cmdHiddenDesc;
	positional_options_description posCmdDesc;
};

#endif /* end of include guard: OPTIONS_H__ */
