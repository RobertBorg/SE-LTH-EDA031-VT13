#include "server_options.h"

int main(int argc, char* argv[]) {
	ServerOptions o(argc,argv);
	o();
	return 0;
}
