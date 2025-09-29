#include "IPManager.h"
#include "INetworkBackend.h"
#include "Utils.h"

IPManager::IPManager(INetworkBackend* backend)
    : networkBackend(backend) {
}

void IPManager::viewCurrentConfiguration() {
    if (networkBackend) networkBackend->viewCurrentConfiguration();
}

void IPManager::setStaticIP(const std::string& ipAddress, const std::string& subnetMask, const std::string& gateway) {
    if (networkBackend) networkBackend->setStaticIP(ipAddress, subnetMask, gateway);
}

void IPManager::enableDHCP() {
    if (networkBackend) networkBackend->enableDHCP();
}

void IPManager::changeDNSServers(const std::string& primaryDNS, const std::string& secondaryDNS) {
    if (networkBackend) networkBackend->changeDNSServers(primaryDNS, secondaryDNS);
}

void IPManager::resetDNS() {
    if (networkBackend) networkBackend->resetFlushDNS();
}