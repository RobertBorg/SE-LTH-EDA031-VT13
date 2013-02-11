class Coding {
public:
	static char encode(char& c);
	static char decode(char& c);
	static int process(char(*processChar)(char& in), int argc, const char* argv[] );
private:
	Coding();

};