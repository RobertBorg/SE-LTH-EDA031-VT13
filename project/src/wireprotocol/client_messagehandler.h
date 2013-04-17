#ifndef CLIENT_MESSAGEHANDLER_H__
#define CLIENT_MESSAGEHANDLER_H__

#include "../../lib/clientserver/protocol.h"
#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::make_shared;
using std::shared_ptr;
using std::dynamic_pointer_cast;
#include "num_p.h"
#include "all_packets.h"


class ClientMessageHandler {
public:
	void parsePkg(Connection& conn) {
		uint8_t pkgType = conn.peek();
		//while(true) {
		//	cout << static_cast<unsigned int>(conn.read()) << endl;
		//}
		shared_ptr<AnsPacket<Connection, Connection>> packet;
		switch(pkgType) {
			case protocol::Protocol::ANS_LIST_NG:
				packet = shared_ptr<AnsPacket<Connection, Connection>>(new AnsListNewsgroupPacket<Connection, Connection>());
				conn >> *dynamic_pointer_cast<AnsListNewsgroupPacket<Connection, Connection>>(packet);
				break;
			case protocol::Protocol::ANS_CREATE_NG:
				packet = shared_ptr<AnsPacket<Connection, Connection>>(new AnsCreateNewsgroupPacket<Connection, Connection>());
				conn >> *dynamic_pointer_cast<AnsCreateNewsgroupPacket<Connection, Connection>>(packet);
				break;
			case protocol::Protocol::ANS_DELETE_NG:
				packet = shared_ptr<AnsPacket<Connection, Connection>>(new AnsDeleteNewsgroupPacket<Connection, Connection>());
				conn >> *dynamic_pointer_cast<AnsDeleteNewsgroupPacket<Connection, Connection>>(packet);
				break;
			case protocol::Protocol::ANS_LIST_ART:
				packet = shared_ptr<AnsPacket<Connection, Connection>>(new AnsListArtPacket<Connection, Connection>());
				conn >> *dynamic_pointer_cast<AnsListArtPacket<Connection, Connection>>(packet);
				break;
			case protocol::Protocol::ANS_CREATE_ART:
				packet = shared_ptr<AnsPacket<Connection, Connection>>(new AnsCreateArticlePacket<Connection, Connection>());
				conn >> *dynamic_pointer_cast<AnsCreateArticlePacket<Connection, Connection>>(packet);
				break;
			case protocol::Protocol::ANS_DELETE_ART:
				packet = shared_ptr<AnsPacket<Connection, Connection>>(new AnsDeleteArticlePacket<Connection, Connection>());
				conn >> *dynamic_pointer_cast<AnsDeleteArticlePacket<Connection, Connection>>(packet);
				break;
			case protocol::Protocol::ANS_GET_ART:
				packet = shared_ptr<AnsPacket<Connection, Connection>>(new AnsGetArticlePacket<Connection, Connection>());
				conn >> *dynamic_pointer_cast<AnsGetArticlePacket<Connection, Connection>>(packet);
				break;
			default:
				throw SeralizationViolationException();
				break;
		}

		packet->process();
	}

};

#endif /* end of include guard: CLIENT_MESSAGEHANDLER_H__ */