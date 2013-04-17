#include "client_options.h"
#include <string>
#include <boost/any.hpp>
#include <iostream>
#include "../lib/clientserver/connection.h"
#include "wireprotocol/all_packets.h"
#include "wireprotocol/client_messagehandler.h"
#include "database/database.h"

using std::shared_ptr;
using std::map;

using client_server::Connection;
using std::cerr;

void notEnoughParameters(){

	// Här händer nåt kul
}



int main(int argc, char* argv[]) {
	ClientOptions o(argc,argv);
	o();
	if( o.count("server-address") && o.count("server-port") && o.count("mode-of-operation")) {
		std::string adr = o["server-address"].as<std::string>();
		uint16_t port = o["server-port"].as<uint16_t>();
		Connection connection(adr.c_str(), port);
		if (! connection.isConnected()) {
        	cerr << "Connection attempt failed" << endl;
        	exit(1);
    	}
    	ClientMessageHandler msgHandler;
    	std::string mode = o["mode-of-operation"].as<std::string>();

    	if (mode == "list-newsgroup"){
    		ComListNewsgroupPacket<DummyDatabase> pkt;
    		connection << pkt;

    	} else if (mode ==  "create-newsgroup"){
    		if (o.count("pos2")){
    			ComCreateNewsGroupPacket<DummyDatabase> pkt(o["pos2"].as<std::string>());
    			connection << pkt;
    		} else {
    			notEnoughParameters();
    		}

    	} else if (mode ==  "delete-newsgroup"){

    		if (o.count("pos2")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			ComDeleteNewsgroupPacket<DummyDatabase> pkt(static_cast<uint32_t>(value));
    			connection << pkt;
    		} else {
    			notEnoughParameters();
    		}


    	} else if (mode ==  "list-article"){

    		if (o.count("pos2")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			ComListArticlePacket<DummyDatabase> pkt(static_cast<uint32_t>(value));
    			connection << pkt;
    		} else {
    			notEnoughParameters();
    		}


    	} else if (mode ==  "create-article"){
    		if (o.count("pos2") && o.count("pos3") && o.count("pos4") && o.count("pos5")){

    			int value = atoi(o["pos2"].as<string>().c_str());
    			std::string title = o["pos3"].as<string>();
    			std::string author = o["pos4"].as<string>();
    			std::string text = o["pos5"].as<string>();
    			ComCreateArtPacket<DummyDatabase> pkt(static_cast<uint32_t>(value), title, author, text);
    			connection << pkt;
    		} else {
    			notEnoughParameters();
    		}


    	} else if (mode ==  "delete-article"){

    		if (o.count("pos2") && o.count("pos3")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			int value2 = atoi(o["pos3"].as<string>().c_str());
    			ComDeleteArticlePacket<DummyDatabase> pkt(static_cast<uint32_t>(value), static_cast<uint32_t>(value2));
    			connection << pkt;
    		} else {
    			notEnoughParameters();
    		}


    	} else if (mode ==  "get-article"){
    		if (o.count("pos2") && o.count("pos3")){
    			int value = atoi(o["pos2"].as<string>().c_str());
    			int value2 = atoi(o["pos3"].as<string>().c_str());
    			ComGetArtPacket<DummyDatabase> pkt(static_cast<uint32_t>(value), static_cast<uint32_t>(value2));
    			connection << pkt;
    		} else {
    			notEnoughParameters();
    		}

    	} else {
            cout << "unsupported mode-of-operation" << endl;
            return 0;
        }
    	msgHandler.parsePkg(connection);
	}
	return 0;
}
