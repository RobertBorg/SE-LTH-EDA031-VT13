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
		//while(true) {
		//	cout << static_cast<unsigned int>(conn.read()) << endl;
		//}
		//cout << static_cast<unsigned int>(packetType) << endl;
		shared_ptr<ComPacket<Database> > packet;
		switch(packetType){
			case protocol::Protocol::COM_LIST_NG:
				packet = shared_ptr<ComPacket<Database> >(new ComListNewsgroupPacket<Database>()) ;
				break;
			case protocol::Protocol::COM_CREATE_NG:
				packet = shared_ptr<ComPacket<Database> >(new ComCreateNewsGroupPacket<Database>()) ;
				break;
			case protocol::Protocol::COM_DELETE_NG:
				packet = shared_ptr<ComPacket<Database> >(new ComDeleteNewsgroupPacket<Database>()) ;
				break;
			case protocol::Protocol::COM_LIST_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComListArticlePacket<Database>()) ;
				break;
			case protocol::Protocol::COM_CREATE_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComCreateArtPacket<Database>()) ;
				break;
			case protocol::Protocol::COM_DELETE_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComDeleteArticlePacket<Database>()) ;
				break;
			case protocol::Protocol::COM_GET_ART:
				packet = shared_ptr<ComPacket<Database> >(new ComGetArtPacket<Database>()) ;
				break;
			default:
				throw SeralizationViolationException();
				break;
		}
		packet->read(conn);
		return packet;
	}
};

#endif /* end of include guard: SERVER_MESSAGEHANDLER_H__ */
