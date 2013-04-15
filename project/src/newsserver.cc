#include "server_options.h"
#include "wireprotocol/packet.h"
#include "wireprotocol/server_messagehandler.h"
#include "database/in_memory_database.h"
#include "../lib/clientserver/connection.h"

#include <memory>
using std::shared_ptr;

using namespace client_server;
using std::cout;
using std:: cerr;

int main(int argc, char* argv[]) {
	ServerOptions o(argc,argv);
	o();
	uint16_t port = o["server-port"].as<uint16_t>();
	Server server(port);

	if (! server.isReady()) {
        cerr << "Server initialization error" << endl;
        exit(1);
    }

    ServerMessageHandler<InMemoryDatabase> msgHandler;
    InMemoryDatabase db;

    while (true) {
        Connection* conn = server.waitForActivity();
        if (conn != 0) {
            try {
                shared_ptr<ComPacket<InMemoryDatabase> > packet = msgHandler.parsePkg(*conn);
                shared_ptr<AnsPacket> ansPacket = packet->process(db);
                *conn << *ansPacket;
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
	return 0;
}
