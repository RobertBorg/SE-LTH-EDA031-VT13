#ifndef COM_GET_ART_H__
#define COM_GET_ART_H__

class ComGetArtPacket : public ComPacket {
public:
	ComGetArtPacket() = default;
	ComGetArtPacket(int &newsGroupNumber_, int &articleNumber_) : newsGroupNumber(newsGroupNumber_), articleNumber(articleNumber_) {}
	virtual shared_ptr<AnsPacket> process(Database *db) const {

	}
private:
	int newsGroupNumber;
	int articleNumber;

};

Connection& operator>>(Connection &inConn, ComGetArtPacket &rhs) {
	eat(protocol::COM_GET_ART);
	num_p groupNum, artNum;
	inConn >> groupNum >> artNum;
	eat(protocol::COM_END);

	newsGroupNumber = groupNum;
	articleNumber = artNum;

	return in;
}

Connection& operator<<(Connection &outConn, ComGetArtPacket &rhs) {
	outConn << protocol::COM_GET_ART;
	outConn << num_p(newsGroupNumber) << num_p(artNum);
	outConn << protocol::COM_END;
	return outConn;
}

#endif /* end of include guard: COM_GET_ART_H__ */