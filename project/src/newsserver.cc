#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <memory>
using std::shared_ptr;


#include "../lib/clientserver/connection.h"
using namespace client_server;


#include "server_options.h"
#include "wireprotocol/packet.h"
#include "wireprotocol/server_messagehandler.h"
#include "database/in_memory_database.h"
#include "database/on_file_database.h"


template <typename Database>
void mainLoop(Server &server, ServerMessageHandler<Database> &msgHandler, Database &db) {
    while (true) {
        Connection* conn = server.waitForActivity();
        if (conn != 0) {
            try {
                shared_ptr<ComPacket<Database> > packet = msgHandler.parsePkg(*conn);
                shared_ptr<AnsPacket<Connection, Connection> > ansPacket = packet->process(db);
                ansPacket->write(*conn);
            }
            catch (ConnectionClosedException&) {
                server.deregisterConnection(conn);
                delete conn;
                cout << "Client closed connection" << endl;
            }
        }
        else {
            server.registerConnection(new Connection);
            cout << "New client connects" << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    ServerOptions o(argc,argv);
    o();
    if(!o.count("server-port")) {
        return 0;
    }
	uint16_t port = o["server-port"].as<uint16_t>();
	Server server(port);

	if (! server.isReady()) {
        cerr << "Server initialization error" << endl;
        exit(1);
    }

    if(o["persistent-db"].as<bool>()){
        //cerr << "on file db not implemented" << endl;
        ServerMessageHandler<OnFileDatabase> msgHandler;
        OnFileDatabase db;
        mainLoop(server, msgHandler, db);
    } else {
        ServerMessageHandler<InMemoryDatabase> msgHandler;
        InMemoryDatabase db;
        mainLoop(server, msgHandler, db);
    }


	return 0;
}
