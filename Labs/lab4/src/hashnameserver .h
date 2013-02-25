#ifndef HASHNAMESERVER_H__
#define HASHNAMESERVER_H__

#include "hash_map.h"
#include "nameserver/nameserverinterface.h"

using namespace cpp_lab4;

class HashNameServer : public NameServerInterface {

//	typedef pair<const HostName, IPAddress> NSPair;
//	typedef hash_map<const HostName, IPAddress> NSMap;
public:

    /*
     * Insert a name/address pair. Does not check if the name
     * or address already exists.
     */
    virtual void insert(const HostName& hostName, const IPAddress& iP) {

    } 
    
    /*
     * Remove the pair with the specified host name. Returns true
     * if the host name existed and the pair was removed, false
     * otherwise.
     */
    virtual bool remove(const HostName& hostName)  {

    }
    
    /*
     * Find the IP address for the specified host name. Returns
     * NON_EXISTING_ADDRESS if the host name wasn't in the name
     * server.
     */
    virtual IPAddress lookup(const HostName& hostName) const {

    }
private:
	Hash_Map hash_map;

};



#endif