#ifndef CLIENT_MESSAGEHANDLER_H__
#define CLIENT_MESSAGEHANDLER_H__

#include "iostream_news.h"
#include "../../lib/clientserver/protocol.h"
#include <iostream>
#include "num_p.h"


class ClientMessageHandler {
public:
	shared_ptr<Packet> parsePkg(Connection& conn) {
		uint8_t pkgType = conn.peek();
		shared_ptr<ComPacket> packet;
		switch(pkgType) {
			case protocol::ANS_LIST_NG:
				packet(new AnsListNewsgroupPacket());
				conn << &packet;
				break;
			case protocol::ANS_CREATE_NG:
				packet(new AnsCreateNewsgroupPacket());
				conn << &packet;
				break;
			case protocol::ANS_DELETE_NG:
				packet(new AnsDeleteNewsgroupPacket());
				conn << &packet;
				break;
			case protocol::ANS_LIST_ART:
				packet(new AnsListArtPacket());
				conn << &packet;
				break;
			case protocol::ANS_CREATE_ART:
				packet(new AnsCreateArticlePacket());
				conn << &packet;
				break;
			case protocol::ANS_DELETE_ART:
				packet(new AnsDeleteArticlePacket());
				conn << &packet;
				break;
			case protocol::ANS_GET_ART:
				packet(new AnsGetArticlePacket());
				conn << &packet;
				break;
			default:
				throw ProtocolViolationException();
				break;

		}
	}
};

#endif /* end of include guard: CLIENT_MESSAGEHANDLER_H__ */