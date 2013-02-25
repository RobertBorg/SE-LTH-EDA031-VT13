#ifndef HASHMAP_H__
#define HASHMAP_H__

#include <vector>
using std::vector;

#include <utility>
using std::pair;
#include "nameserver/nameserverinterface.h"
#include <algorithm>
using std::find_if;
using namespace cpp_lab4;

struct EraseComparator {
	EraseComparator(HostName hostName) : name(hostName) {}

	bool operator()(const pair<const HostName, IPAddress>& pair) {
		return pair.first == name;
	}

private:
	HostName name;
};

class Hash_Map {

typedef pair<const HostName, IPAddress> NSPair;
typedef vector<vector< NSPair > > Map;


public:

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

	vector<NSPair>::iterator find (const HostName& key) const {
		const vector<NSPair>& toFind = map[hashFunction(key) % map.size()];
		EraseComparator finder(key);
		vector<NSPair>::const_iterator begin= toFind.begin();
		vector<NSPair>::const_iterator end = toFind.end();
		return find_if(begin, end, finder);
	}


private:
	Map map;

	//REDO
	size_t hashFunction(const HostName& key) const {
		return key.length();
	}
};


#endif