#include "client_options.h"
#include <string>
#include <boost/any.hpp>
#include <iostream>
#include "../lib/clientserver/connection.h"

using client_server::Connection;

int main(int argc, char* argv[]) {
	ClientOptions o(argc,argv);
	o();
	if( o.count("server-address") && o.count("server-address")) {
		std::string adr = o["server-address"].as<std::string>();
		uint16_t port = o["server-port"].as<uint16_t>();
		Connection *connection = new Connection(adr.c_str(), port);
		cout << adr << ":" << port << endl;
	}




	return 0;
}
