#include "LinuxNetwork.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void LinuxNetwork::viewCurrentConfiguration() {
    system("ip addr show");
}

void LinuxNetwork::setStaticIP(const string& ipAddress, const string& subnetMask, const string& gateway) {
    string command = "sudo ifconfig eth0 " + ipAddress + " netmask " + subnetMask;
    system(command.c_str());
    if (!gateway.empty()) {
        string gwCommand = "sudo route add default gw " + gateway + " eth0";
        system(gwCommand.c_str());
    }
}

void LinuxNetwork::enableDHCP() {
    system("sudo dhclient eth0");
}

void LinuxNetwork::changeDNSServers(const string& primaryDNS, const string& secondaryDNS) {
    string command = "echo 'nameserver " + primaryDNS + "' | sudo tee /etc/resolv.conf";
    system(command.c_str());
    if (!secondaryDNS.empty()) {
        command = "echo 'nameserver " + secondaryDNS + "' | sudo tee -a /etc/resolv.conf";
        system(command.c_str());
    }
}

void LinuxNetwork::resetFlushDNS() {
    system("sudo systemd-resolve --flush-caches");
}