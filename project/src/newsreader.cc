#include "client_options.h"

int main(int argc, char* argv[]) {
	ClientOptions o(argc,argv);
	o();
	return 0;
}
