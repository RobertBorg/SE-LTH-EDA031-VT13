#ifndef COM_GET_ART_H__
#define COM_GET_ART_H__

class ComGetArtPacket : public ComPacket {
public:
	ComGetArt(int &newsGroupNumber_, int &articleNumber_) : newsGroupNumber(newsGroupNumber_), articleNumber(articleNumber_) {}
	virtual shared_ptr<AnsPacket> process(Database *db) const {

	}
private:
	int newsGroupNumber;
	int articleNumber;

};

istream_news& operator>>(istream_news &in, ComGetArtPacket &rhs) {
	in.eat(protocol::COM_GET_ART);
	num_p groupNum, artNum;
	in >> groupNum >> artNum;
	in.eat(protocol::COM_END);

	newsGroupNumber = groupNum;
	articleNumber = artNum;

	return in;
}

iostream_news& operator<<(iostream_news &out, ComGetArtPacket &rhs) {
	out << protocol::COM_GET_ART;
	out << num_p(newsGroupNumber) << num_p(artNum);
	out << protocol::COM_END;
	return out;
}

#endif /* end of include guard: COM_GET_ART_H__ */