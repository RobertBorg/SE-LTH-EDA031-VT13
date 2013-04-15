#ifndef CLIENT_MESSAGEHANDLER_H__
#define CLIENT_MESSAGEHANDLER_H__

#include "../../lib/clientserver/protocol.h"
#include <iostream>
using std::cout;
using std::endl;
#include "num_p.h"
#include "all_packets.h"


class ClientMessageHandler {
public:
	void parsePkg(Connection& conn) {
		uint8_t pkgType = conn.peek();
		cout << pkgType << endl;
		shared_ptr<AnsPacket> packet;
		switch(pkgType) {
			case protocol::Protocol::ANS_LIST_NG:
				packet = shared_ptr<AnsPacket>(new AnsListNewsgroupPacket());
				conn >> *packet;
				break;
			case protocol::Protocol::ANS_CREATE_NG:
				packet = shared_ptr<AnsPacket>(new AnsCreateNewsgroupPacket());
				conn >> *packet;
				break;
			case protocol::Protocol::ANS_DELETE_NG:
				packet = shared_ptr<AnsPacket>(new AnsDeleteNewsgroupPacket());
				conn >> *packet;
				break;
			case protocol::Protocol::ANS_LIST_ART:
				packet = shared_ptr<AnsPacket>(new AnsListArtPacket());
				conn >> *packet;
				break;
			case protocol::Protocol::ANS_CREATE_ART:
				packet = shared_ptr<AnsPacket>(new AnsCreateArticlePacket());
				conn >> *packet;
				break;
			case protocol::Protocol::ANS_DELETE_ART:
				packet = shared_ptr<AnsPacket>(new AnsDeleteArticlePacket());
				conn >> *packet;
				break;
			case protocol::Protocol::ANS_GET_ART:
				packet = shared_ptr<AnsPacket>(new AnsGetArticlePacket());
				conn >> *packet;
				break;
			default:
				throw ProtocolViolationException();
				break;

		}

		packet->process();
	}

};

#endif /* end of include guard: CLIENT_MESSAGEHANDLER_H__ */