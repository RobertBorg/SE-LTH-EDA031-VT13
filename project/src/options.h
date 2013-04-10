#ifndef OPTIONS_H__
#define OPTIONS_H__

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <boost/program_options.hpp>

using namespace boost::program_options;

class Options : private variables_map {
public:
	using variables_map::operator[];
	using variables_map::count;
	Options(int argc, char* argv[]) : cmdDesc("Allowed options"), cmdHiddenDesc("Hidden command line oprtions"), cmdDummyCommandsDesc("Commands") {
		cmdDesc.add_options()
			("mongo-address", value<string>()->default_value("localhost"), "mongodb address")
			("help", "produce help message");

		cmdHiddenDesc.add_options()
			("help", "produce help message")
			("mode-of-operation", value<int>(), "set mode of operation")
			("mongo-address", value<string>()->default_value("localhost"), "mongodb address");


		posCmdDesc.add("mode-of-operation", 1);
		

		store(command_line_parser(argc, argv).options(cmdHiddenDesc).positional(posCmdDesc).run(), *this);
		notify();
	}
	Options& operator() () {
		if(!count("mode-of-operation") || count("help")) {
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
