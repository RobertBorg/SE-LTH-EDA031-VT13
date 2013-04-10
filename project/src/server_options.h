#ifndef SERVER_OPTIONS_H__
#define SERVER_OPTIONS_H__

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <boost/program_options.hpp>

using namespace boost::program_options;

class ServerOptions : private variables_map {
public:
	using variables_map::operator[];
	using variables_map::count;
	ServerOptions(int argc, char* argv[]) : cmdDesc("Allowed options"), cmdHiddenDesc("Hidden command line oprtions") {
		cmdDesc.add_options()
			("help", "produce help message"),
			("non-persistent", "non-persistent in memory database"),
			("persistent", "persistent on disk database");

		cmdHiddenDesc.add_options()
			("help", "produce help message")
			("mode-of-operation", value<int>(), "set mode of operation")
			("pos2", value<string>(), "set mode of operation")
			("pos3", value<string>(), "set mode of operation")
			("pos4", value<string>(), "set mode of operation")
			("pos5", value<string>(), "set mode of operation");


		posCmdDesc.add("mode-of-operation", 1)
		.add("pos2", 2)
		.add("pos3", 3)
		.add("pos4", 4)
		.add("pos5", 5);
		

		store(command_line_parser(argc, argv).options(cmdHiddenDesc).positional(posCmdDesc).run(), *this);
		notify();
	}
	ServerOptions& operator() () {
		if(!count("mode-of-operation") || count("help")) {
			cout << 
			"Usage:" << endl <<
			"newsreader [options] " << endl <<
			"options:" << endl <<
			"list-newsgroup - lists all news groups and their ids" << endl <<
			"create-newsgroup [title] - creates a newsgroup with title [title]" << endl;
			

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
