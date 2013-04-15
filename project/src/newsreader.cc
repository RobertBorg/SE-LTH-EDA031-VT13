#include "client_options.h"
#include <string>
#include <boost/any.hpp>
#include <iostream>
#include "../lib/clientserver/connection.h"
#include "wireprotocol/all_packets.h"

using client_server::Connection;

void notEnoughParameters(){

	// Här händer nåt kul
}
int main(int argc, char* argv[]) {
	ClientOptions o(argc,argv);
	o();
	if( o.count("server-address") && o.count("server-address")) {
		std::string adr = o["server-address"].as<std::string>();
		uint16_t port = o["server-port"].as<uint16_t>();
		Connection *connection = new Connection(adr.c_str(), port);
		if (! conn.isConnected()) {
        	cerr << "Connection attempt failed" << endl;
        	exit(1);
    	}
    	ClientMessageHandler msgHandler();
    	std::string mode = o["mode-of-operation"].as<std::string>();

    	if (mode == "list-newsgroup"){
    		ComListNewsgroupPacket pkt();
    		conn >> pkt;

    	} else if (mode ==  "create-newsgroup"){
    		if (o.count("pos2")){
    			ComCreateNewsGroupPacket pkt(o["pos2"].as<std::string>());
    			conn >> pkt;
    		} else {
    			notEnoughParameters()
    		}

    	} else if (mode ==  "delete-newsgroup"){

    		if (o.count("pos2")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			ComDeleteNewsgroupPacket pkt(static_cast<uint32_t>(value));
    			conn >> pkt;
    		} else {
    			notEnoughParameters()
    		}


    	} else if (mode ==  "list-article"){

    		if (o.count("pos2")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			ComListArticlePacket pkt(static_cast<uint32_t>(value));
    			conn >> pkt;
    		} else {
    			notEnoughParameters()
    		}


    	} else if (mode ==  "create-article"){
    		if (o.count("pos2") && o.count("pos3") && o.count("pos4") && o.count("pos5")){

    			int value = atoi(o["pos2"].as<string>().c_str());
    			std::string title = ["pos3"].as<string>();
    			std::string author = ["pos4"].as<string>();
    			std::string text = ["pos5"].as<string>();
    			ComCreateArtPacket pkt(static_cast<uint32_t>(value), title, author, text);
    			conn >> pkt;
    		} else {
    			notEnoughParameters()
    		}


    	} else if (mode ==  "delete-article"){

    		if (o.count("pos2") && o.count("pos3")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			int value2 = atoi(o["pos3"].as<string>().c_str());
    			ComDeleteArticlePacket pkt(static_cast<uint32_t>(value), static_cast<uint32_t>(value2));
    			conn >> pkt;
    		} else {
    			notEnoughParameters()
    		}


    	} else if (mode ==  "get-article"){
    		AnsGetArticlePacket
    		if (o.count("pos2") && o.count("pos3")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			int value2 = atoi(o["pos3"].as<string>().c_str());
    			ComGetArtPacket pkt(static_cast<uint32_t>(value), static_cast<uint32_t>(value2));
    			conn >> pkt;
    		} else {
    			notEnoughParameters()
    		}

    	}
    	msgHandler.parsePkg(conn);
	}
	return 0;
}
