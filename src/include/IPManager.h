#ifndef IP_MANAGER_H
#define IP_MANAGER_H

#include <string>
#include "INetworkBackend.h"

class IPManager {
public:
    IPManager(INetworkBackend* backend);
    
    void viewCurrentConfiguration();
    void setStaticIP(const std::string& ipAddress, const std::string& subnetMask, const std::string& gateway);
    void enableDHCP();
    void changeDNSServers(const std::string& primaryDNS, const std::string& secondaryDNS);
    void resetDNS();

private:
    INetworkBackend* networkBackend;
};

#endif // IP_MANAGER_H