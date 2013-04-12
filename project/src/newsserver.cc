#include "server_options.h"
#include "packet.h"

using namespace client_server;

int main(int argc, char* argv[]) {
	ServerOptions o(argc,argv);
	o();
	uint16_t port = o["server-port"].as<uint16_t>();
	Server server(port);

	if (! server.isReady()) {
        cerr << "Server initialization error" << endl;
        exit(1);
    }

    ServerMessageHandler msgHandler();
    InMemoryDatabase db();

    while (true) {
        Connection* conn = server.waitForActivity();
        if (conn != 0) {
            try {
                boost::shared_ptr<ComPacket> packet = msgHandler.parsePkg(conn);
                boost::shared_ptr<AnsPacket> ansPacket = packet->process(db);
                conn << *ansPacket;
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
