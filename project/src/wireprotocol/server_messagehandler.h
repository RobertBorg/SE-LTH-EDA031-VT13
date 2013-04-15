#ifndef SERVER_MESSAGEHANDLER_H__
#define SERVER_MESSAGEHANDLER_H__

#include "../../lib/clientserver/protocol.h"
#include "all_packets.h"
#include <iostream>

template <typename ComPacket>
class ServerMessageHandler {
public:
	shared_ptr<ComPacket> parsePkg(Connection& conn) {
		uint8_t packetType;
		packetType = conn.peek();
		shared_ptr<ComPacket> packet;
		switch(packetType){
			
			case protocol::Protocol::COM_LIST_NG:
				packet(new ComListNewsgroupPacket()) ;
				conn >> &packet;
			break;

			case protocol::Protocol::COM_CREATE_NG:
				packet(new ComCreateNewsGroupPacket()) ;
				conn >> &packet;

				break;

			case protocol::Protocol::COM_DELETE_NG:
				packet(new ComDeleteNewsgroupPacket()) ;
				conn >> &packet;
				break;


			case protocol::Protocol::COM_LIST_ART:
				packet(new ComListArticlePacket()) ;
				conn >> &packet;
				break;

			case protocol::Protocol::COM_CREATE_ART:
				packet(new ComCreateArtPacket()) ;
				conn >> &packet;
				break;

			case protocol::Protocol::COM_DELETE_ART:
				packet(new ComDeleteArticlePacket()) ;
				conn >> &packet;
				break;

			case protocol::Protocol::COM_GET_ART:
				packet(new ComGetArtPacket()) ;
				conn >> &packet;
				break;

			case default:
				throw ProtocolViolationException();
				break;

		}

		return packet;
	}
};

#endif /* end of include guard: SERVER_MESSAGEHANDLER_H__ */
