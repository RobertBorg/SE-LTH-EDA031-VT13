#ifndef MAPNAMESERVER_H__
#define MAPNAMESERVER_H__

#include "nameserver/nameserverinterface.h"
#include <map>
using std::map;
#include <utility>
using std::pair;

using namespace cpp_lab4;

class MapNameServer : public NameServerInterface {

	typedef pair<const HostName, IPAddress> NSPair;
	typedef map<const HostName, IPAddress> NSMap;

	
public:

    /*
     * Insert a name/address pair. Does not check if the name
     * or address already exists.
     */
    virtual void insert(const HostName& hostName, const IPAddress& iP) {
    	NSPair toInsert(hostName, iP);
    	lookupMap.insert(toInsert);
    }
    
    /*
     * Remove the pair with the specified host name. Returns true
     * if the host name existed and the pair was removed, false
     * otherwise.
     */
    virtual bool remove(const HostName& hostName) {
    	NSMap::iterator it;
    	it = lookupMap.find(hostName);
    	if(it != lookupMap.end()) {
    		lookupMap.erase(it);
    		return true;
    	} else {
    		return false;
    	}
    }
    
    /*
     * Find the IP address for the specified host name. Returns
     * NON_EXISTING_ADDRESS if the host name wasn't in the name
     * server.
     */
    virtual IPAddress lookup(const HostName& hostName) const {
    	NSMap::const_iterator it;
    	it = lookupMap.find(hostName);
    	if(it != lookupMap.end()) {
    		return it->second;
    	} else {
    		return NON_EXISTING_ADDRESS;
    	}
    }

private:
	NSMap lookupMap;
};

#endif
