#include "LinuxNetwork.h"
#include <iostream>
#include <cstdlib>

void LinuxNetwork::viewCurrentConfiguration() {
    std::system("ip addr show");
}

void LinuxNetwork::setStaticIP(const std::string& ipAddress, const std::string& subnetMask, const std::string& gateway) {
    std::string command = "sudo ifconfig eth0 " + ipAddress + " netmask " + subnetMask;
    std::system(command.c_str());
    if (!gateway.empty()) {
        std::string gwCommand = "sudo route add default gw " + gateway + " eth0";
        std::system(gwCommand.c_str());
    }
}

void LinuxNetwork::enableDHCP() {
    std::system("sudo dhclient eth0");
}

void LinuxNetwork::changeDNSServers(const std::string& primaryDNS, const std::string& secondaryDNS) {
    std::string command = "echo 'nameserver " + primaryDNS + "' | sudo tee /etc/resolv.conf";
    std::system(command.c_str());
    if (!secondaryDNS.empty()) {
        command = "echo 'nameserver " + secondaryDNS + "' | sudo tee -a /etc/resolv.conf";
        std::system(command.c_str());
    }
}

void LinuxNetwork::resetFlushDNS() {
    std::system("sudo systemd-resolve --flush-caches");
}