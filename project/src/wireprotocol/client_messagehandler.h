#ifndef CLIENT_MESSAGEHANDLER_H__
#define CLIENT_MESSAGEHANDLER_H__

#include "iostream_news.h"
#include "../../lib/clientserver/protocol.h"
#include <iostream>
#include "num_p.h"


using std::cerr;
using std::endl;

class ClientMessageHandler {
public:
	shared_ptr<Package> parsePkg(iostream_news& in) {
		uint8_t pkgType;
		in >> pkgType;
		switch(pkgType) {
			case protocol::ANS_LIST_NG:
				num_p numNewsGroups;
				in >> numNewsGroups;
				
				break;
			case protocol::ANS_CREATE_NG:
				break;
			case protocol::ANS_DELETE_NG:
				break;
			case protocol::ANS_LIST_ART:
				break;
			case protocol::ANS_CREATE_ART:
				break;
			case protocol::ANS_DELETE_ART:
				break;
			case protocol::ANS_GET_ART:
				break;
			default:
				cerr << "unknown packagetype received: " << static_cast<unsigned int>(pkgType) << endl;
				break;

		}
	}
};

#endif /* end of include guard: CLIENT_MESSAGEHANDLER_H__ */