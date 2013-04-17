#ifndef CLIENT_OPTIONS_H__
#define CLIENT_OPTIONS_H__

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <boost/program_options.hpp>

using namespace boost::program_options;

class ClientOptions : private variables_map {
public:
	using variables_map::operator[];
	using variables_map::count;
	ClientOptions(int argc, char* argv[]) 
	: cmdDesc("Allowed options")
	, cmdHiddenDesc("Hidden command line oprtions")  {
		cmdDesc.add_options()
			("help", "produce help message")
			("server-address,A", value<string>(), "NNTP server address")
			("server-port,P",value<uint16_t>() ,"NNTP server port");

		cmdHiddenDesc.add_options()
			("help", "produce help message")
			("server-address,A", value<string>(), "NNTP server address")
			("server-port,P",value<uint16_t>() ,"NNTP server port")
			("mode-of-operation", value<string>(), "set mode of operation")
			("pos2", value<string>(), "set mode of operation")
			("pos3", value<string>(), "set mode of operation")
			("pos4", value<string>(), "set mode of operation")
			("pos5", value<string>(), "set mode of operation");


		posCmdDesc
			.add("mode-of-operation", 1)
			.add("pos2", 1)
			.add("pos3", 1)
			.add("pos4", 1)
			.add("pos5", 1);
		

		store(command_line_parser(argc, argv).options(cmdHiddenDesc).positional(posCmdDesc).run(), *this);
		notify();
	}
	ClientOptions& operator() () {
		if(!count("mode-of-operation") || count("help")) {
			cout << 
			"Usage:" << endl <<
			"newsreader [options] [string mode-of-operation] " << endl <<
			"mode-of-operations:" << endl <<
			"list-newsgroup - lists all news groups and their ids" << endl <<
			"create-newsgroup [string title] - creates a newsgroup with title [string title]" << endl <<
			"delete-newsgroup [int id] - deletes newsgroup with id [id]" << endl <<
			"list-article [int newsgroup] - lists articles title and their ids from newsgroup [int newsgroup]" << endl <<
			"create-article [int id] [string title] [string author] [string text] - creates an article in newsgroup [int id]" << endl <<
			"delete-article [int newsgroupId] [int articleId] - deletes article [int articleId] in newsgroup [int newsgroupId]" << endl <<
			"get-article [int newsgroupId] [int articleId] - gets article [int articleId] in newsgroup [int newsgroupId]" << endl;

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
