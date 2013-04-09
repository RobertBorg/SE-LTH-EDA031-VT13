#ifndef SERVER_MESSAGEHANDLER_H__
#define SERVER_MESSAGEHANDLER_H__

#include "iostream_news.h"
#include "protocol.h"
#include "string_p"
#include <iostream>

class ServerMessageHandler {
public:
	shared_ptr<ComPacket> parsePkg(iostream_news& in) {
		uint8_t packetType;
		packeType = in.peek();

		switch(packetType){
			case Protocol::COM_LIST_NG:
				shared_ptr<ComPacket> packet(new ComListArticlePacket()) ;
				in << packet;
			break;

			case Protocol::COM_CREATE_NG:
				break;

			case Protocol::COM_DELETE_NG:
			break;


			case Protocol::COM_LIST_ART:
			break;

			case Protocol::COM_CREATE_ART:
			break;

			case Protocol::COM_DELETE_ART:
			break;

			case Protocol::COM_GET_ART:
			break;

			case default:
				throw ProtocolViolationException();
			break;

		}

		return packet;
	}
};

#endif /* end of include guard: SERVER_MESSAGEHANDLER_H__ */