#ifndef HASHMAP_H__
#define HASHMAP_H__

#include <vector>
using std::vector;

#include <utility>
using std::pair;
#include <algorithm>
using std::find_if;
#include <functional>
using std::hash;


#include "nameserver/nameserverinterface.h"
using namespace cpp_lab4;

struct EraseComparator {
	EraseComparator(HostName hostName) : name(hostName) {}

	bool operator()(const pair<HostName, IPAddress>& pair) {
		return pair.first == name;
	}

private:
	HostName name;
};

class Hash_Map {

typedef pair<HostName, IPAddress> NSPair;
typedef vector<vector< NSPair > > Map;


public:

	Hash_Map(int size) : map(size, vector<NSPair>()) {}

	void insert(const NSPair& val) {
		map[hashFunction(val.first) % map.size()].push_back(val);
	}

	bool erase(const HostName& key) {
		vector<NSPair>& toDelete = map[hashFunction(key) % map.size()];
		EraseComparator eraser(key);
		vector<NSPair>::iterator it = find_if(toDelete.begin(), toDelete.end(), eraser);
		if(it != toDelete.end()) {
			toDelete.erase(it);
			return true;
		}
		return false;
	}

	const IPAddress get (const HostName& key) const {
		const vector<NSPair>& toFind = map[hashFunction(key) % map.size()];
		EraseComparator finder(key);
		vector<NSPair>::const_iterator begin= toFind.begin();
		vector<NSPair>::const_iterator end = toFind.end();
		vector<NSPair>::const_iterator it = find_if(begin, end, finder);
		if(it != toFind.end()) {
			return it->second;
		} else {
			return NON_EXISTING_ADDRESS;
		}
	}


private:
	Map map;

	//REDO
	size_t hashFunction(const HostName& key) const {
		hash<HostName> H;
		return H(key);
	}
};


#endif
