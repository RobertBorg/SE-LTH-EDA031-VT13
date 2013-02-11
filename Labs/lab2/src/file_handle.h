#ifndef FILE_HANDLE_H__
#define FILE_HANDLE_H__

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

class FileHandle {
public:
	FileHandle(const string& filename ) {
		stream.open(filename.c_str());
	}
	~FileHandle() {
		if(stream.is_open()) {
			stream.close();
		}
	}

	ifstream& operator*() {
		return stream;
	}

private:
	ifstream stream;
};

#endif /* end of include guard: FILE_HANDLE_H__ */