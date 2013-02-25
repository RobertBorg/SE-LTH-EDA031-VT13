#ifndef HASHNAMESERVER_H__
#define HASHNAMESERVER_H__

#include "hash_map.h"
#include "nameserver/nameserverinterface.h"

using namespace cpp_lab4;

class HashNameServer : public NameServerInterface, private Hash_Map {
typedef pair<HostName, IPAddress> NSPair;

public:

    HashNameServer(int size) : Hash_Map(size) {}

    /*
     * Insert a name/address pair. Does not check if the name
     * or address already exists.
     */
    virtual void insert(const HostName& hostName, const IPAddress& iP) {
        Hash_Map::insert(NSPair(hostName, iP));
    } 
    
    /*
     * Remove the pair with the specified host name. Returns true
     * if the host name existed and the pair was removed, false
     * otherwise.
     */
    virtual bool remove(const HostName& hostName)  {
        return erase(hostName);
    }
    
    /*
     * Find the IP address for the specified host name. Returns
     * NON_EXISTING_ADDRESS if the host name wasn't in the name
     * server.
     */
    virtual IPAddress lookup(const HostName& hostName) const {
       return get(hostName);
    }
};

#endif
