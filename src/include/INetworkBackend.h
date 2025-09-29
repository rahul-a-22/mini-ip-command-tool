#ifndef INETWORKBACKEND_H
#define INETWORKBACKEND_H

#include <string>

class INetworkBackend {
public:
    virtual ~INetworkBackend() {}

    virtual void viewCurrentConfiguration() = 0;
    virtual void setStaticIP(const std::string& ipAddress, const std::string& subnetMask, const std::string& gateway) = 0;
    virtual void enableDHCP() = 0;
    virtual void changeDNSServers(const std::string& primaryDNS, const std::string& secondaryDNS) = 0;
    virtual void resetFlushDNS() = 0;
};

#endif // INETWORKBACKEND_H