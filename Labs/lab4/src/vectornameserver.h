#ifndef VECTORNAMESERVER_H__
#define VECTORNAMESERVER_H__

#include "nameserver/nameserverinterface.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <algorithm>
using std::find_if;
#include <functional>


using namespace cpp_lab4;

struct HostNameMatcher {
public:
	HostNameMatcher(const HostName& hostName) : toMatch(hostName) {}
	bool match(pair<HostName, IPAddress> pair) {
		return toMatch == pair.first;
	}
private:
	HostName toMatch;
};


class VectorNameServer : public NameServerInterface {
	
	typedef pair<HostName, IPAddress> NSPair;
	typedef vector<NSPair> NSVector;

    /*
     * Insert a name/address pair. Does not check if the name
     * or address already exists.
     */
    virtual void insert(const HostName& hostName, const IPAddress& iPAddress) {
    	lookupDa.push_back(NSPair(hostName, iPAddress));
    }
    
    /*
     * Remove the pair with the specified host name. Returns true
     * if the host name existed and the pair was removed, false
     * otherwise.
     */
    virtual bool remove(const HostName&) {

    }
    
    /*
     * Find the IP address for the specified host name. Returns
     * NON_EXISTING_ADDRESS if the host name wasn't in the name
     * server.
     */
    virtual IPAddress lookup(const HostName& hostName) const {
    	HostNameMatcher matcher(hostName);
    	function<bool, (const NSPair&)> f = [] = (const NSPair& pair) { return matcher.match(pair);};
		NSVector::iterator it = std::find_if (lookupDa.begin(), lookupDa.end(), f);
    }


public:

private:
	NSVector lookupDa;
};


#endif