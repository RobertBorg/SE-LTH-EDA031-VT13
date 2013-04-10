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
	Options(int argc, char* argv[]) : cmdDesc("Allowed options"), cmdHiddenDesc("Hidden command line oprtions") {
		cmdDesc.add_options()
			("help", "produce help message")
			("server-address", value<string>(), "produce help message")
			("server-port",value<uint16_t>() ,"produce help message");

		cmdHiddenDesc.add_options()
			("help", "produce help message")
			("server-address", value<string>(), "produce help message")
			("server-port",value<uint16_t>() ,"produce help message")
			("mode-of-operation", value<string>(), "set mode of operation")
			("pos2", value<string>(), "set mode of operation")
			("pos3", value<string>(), "set mode of operation")
			("pos4", value<string>(), "set mode of operation")
			("pos5", value<string>(), "set mode of operation");


		posCmdDesc
			.add("mode-of-operation", 1)
			.add("pos2", 2)
			.add("pos3", 3)
			.add("pos4", 4)
			.add("pos5", 5);
		

		store(command_line_parser(argc, argv).options(cmdHiddenDesc).positional(posCmdDesc).run(), *this);
		notify();
	}
	Options& operator() () {
		if(!count("mode-of-operation") || count("help")) {
			cout << 
			"Usage:" << endl <<
			"newsreader [options] [mode-of-operation] " << endl <<
			"mode-of-operations:" << endl <<
			"list-newsgroup - lists all news groups and their ids" << endl <<
			"create-newsgroup [title] - creates a newsgroup with title [title]" << endl <<
			"delete-newsgroup [id] - deletes newsgroup with id [id]" << endl <<
			"list-article [newsgroup] - lists articles title and their ids from newsgroup [newsgroup]" << endl <<
			"create-article [id] [title] [author] [text] - creates an article in news group [id]" << endl <<
			"delete-article [newsgroupId] [articleId] - deletes article [articleId] in newsgroup [newsgroupId]" << endl <<
			"get-article [newsgroupId] [articleId] - gets article [articleId] in newsgroup [newsgroupId]" << endl;

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
