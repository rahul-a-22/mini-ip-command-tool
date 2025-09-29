#include "IPManager.h"
#include "INetworkBackend.h"
#include "Utils.h"

using namespace std;

IPManager::IPManager(INetworkBackend* backend)
    : networkBackend(backend) {
}

void IPManager::viewCurrentConfiguration() {
    if (networkBackend) networkBackend->viewCurrentConfiguration();
}

void IPManager::setStaticIP(const string& ipAddress, const string& subnetMask, const string& gateway) {
    if (networkBackend) networkBackend->setStaticIP(ipAddress, subnetMask, gateway);
}

void IPManager::enableDHCP() {
    if (networkBackend) networkBackend->enableDHCP();
}

void IPManager::changeDNSServers(const string& primaryDNS, const string& secondaryDNS) {
    if (networkBackend) networkBackend->changeDNSServers(primaryDNS, secondaryDNS);
}

void IPManager::resetDNS() {
    if (networkBackend) networkBackend->resetFlushDNS();
}