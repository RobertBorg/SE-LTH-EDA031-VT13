#ifndef SERVER_MESSAGEHANDLER_H__
#define SERVER_MESSAGEHANDLER_H__

#include "iostream_news.h"
#include "protocol.h"
#include "string_p"
#include <iostream>

class ServerMessageHandler {
public:
	shared_ptr<ComPacket> parsePkg(Connection& conn) {
		uint8_t packetType;
		packeType = conn.peek();
		shared_ptr<ComPacket> packet;
		switch(packetType){
			
			case protocol::COM_LIST_NG:
				packet(new ComListNewsgroupPacket()) ;
				conn << &packet;
			break;

			case protocol::COM_CREATE_NG:
				packet(new ComCreateNewsGroupPacket()) ;
				conn << &packet;

				break;

			case protocol::COM_DELETE_NG:
				packet(new ComDeleteNewsgroupPacket()) ;
				conn << &packet;
				break;


			case protocol::COM_LIST_ART:
				packet(new ComListArticlePacket()) ;
				conn << &packet;
				break;

			case protocol::COM_CREATE_ART:
				packet(new ComCreateArtPacket()) ;
				conn << &packet;
				break;

			case protocol::COM_DELETE_ART:
				packet(new ComDeleteArticlePacket()) ;
				conn << &packet;
				break;

			case protocol::COM_GET_ART:
				packet(new ComGetArtPacket()) ;
				conn << &packet;
				break;

			case default:
				throw ProtocolViolationException();
				break;

		}

		return packet;
	}
};

#endif /* end of include guard: SERVER_MESSAGEHANDLER_H__ */