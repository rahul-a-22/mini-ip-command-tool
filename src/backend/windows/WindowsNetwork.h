#pragma once

#include "INetworkBackend.h"
#include <string>

class WindowsNetwork : public INetworkBackend {
public:
    WindowsNetwork() = default;
    ~WindowsNetwork() override = default;

    void viewCurrentConfiguration() override;
    void setStaticIP(const std::string& ipAddress, const std::string& subnetMask, const std::string& gateway) override;
    void enableDHCP() override;
    void changeDNSServers(const std::string& primaryDNS, const std::string& secondaryDNS) override;
    void resetFlushDNS() override;
};