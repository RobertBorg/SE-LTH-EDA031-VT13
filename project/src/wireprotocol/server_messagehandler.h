#ifndef SERVER_MESSAGEHANDLER_H__
#define SERVER_MESSAGEHANDLER_H__

#include "../../lib/clientserver/protocol.h"
#include "all_packets.h"
#include <iostream>
using std::cout;
using std::endl;

template <typename Database>
class ServerMessageHandler {
public:
	shared_ptr<ComPacket<Database> > parsePkg(Connection& conn) {
		uint8_t packetType;
		packetType = conn.peek();
		shared_ptr<ComPacket<Database> > packet;
		switch(packetType){
			
			case protocol::Protocol::COM_LIST_NG:

				packet = shared_ptr<ComPacket<Database> >(new ComListNewsgroupPacket<Database>()) ;
				cout << "starting to parse list ng" << endl;
				conn >> *packet;
				cout << "parsing done" << endl;
			break;

			case protocol::Protocol::COM_CREATE_NG:
				packet = shared_ptr<ComPacket<Database> >(new ComCreateNewsGroupPacket<Database>()) ;
				conn >> *packet;

				break;

			case protocol::Protocol::COM_DELETE_NG:
				packet = shared_ptr<ComPacket<Database> >(new ComDeleteNewsgroupPacket<Database>()) ;
				conn >> *packet;
				break;


			case protocol::Protocol::COM_LIST_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComListArticlePacket<Database>()) ;
				conn >> *packet;
				break;

			case protocol::Protocol::COM_CREATE_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComCreateArtPacket<Database>()) ;
				conn >> *packet;
				break;

			case protocol::Protocol::COM_DELETE_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComDeleteArticlePacket<Database>()) ;
				conn >> *packet;
				break;

			case protocol::Protocol::COM_GET_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComGetArtPacket<Database>()) ;
				conn >> *packet;
				break;

			default:
				throw ProtocolViolationException();
				break;

		}

		return packet;
	}
};

#endif /* end of include guard: SERVER_MESSAGEHANDLER_H__ */
