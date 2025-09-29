#include "BackendFactory.h"
#include "IPManager.h"
#include "cli.h"
#include "DNSResolver.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

void displayMenu() {
    std::cout << "Mini IP Command Tool" << std::endl;
    std::cout << "1. View Current IP Configuration" << std::endl;
    std::cout << "2. DNS Resolver (resolve hostname / reverse lookup)" << std::endl;
    std::cout << "3. Set Static IP Address" << std::endl;
    std::cout << "4. Enable DHCP" << std::endl;
    std::cout << "5. Change DNS Servers" << std::endl;
    std::cout << "6. Reset/Flush DNS" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

void handleUserInput(IPManager& ipManager) {
    int choice;
    std::string ipAddress, subnetMask, gateway, dns1, dns2;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                ipManager.viewCurrentConfiguration();
                break;
            case 2: {
                std::cout << "DNS Resolver:\n1) Resolve hostname\n2) Reverse lookup (IP to name)\nChoose: ";
                int sub;
                std::cin >> sub;
                if (sub == 1) {
                    std::cout << "Enter hostname: ";
                    std::string host;
                    std::cin >> host;
                    std::vector<std::string> ips;
                    if (DNSResolver::ResolveHostname(host, ips)) {
                        std::cout << "Resolved IPs:\n";
                        for (auto &a : ips) std::cout << "  " << a << std::endl;
                    } else {
                        std::cout << "Resolution failed for " << host << std::endl;
                    }
                } else if (sub == 2) {
                    std::cout << "Enter IP address: ";
                    std::string ip;
                    std::cin >> ip;
                    std::string name;
                    if (DNSResolver::ReverseLookup(ip, name)) {
                        std::cout << "Hostname: " << name << std::endl;
                    } else {
                        std::cout << "Reverse lookup failed for " << ip << std::endl;
                    }
                } else {
                    std::cout << "Invalid selection." << std::endl;
                }
                break;
            }
            case 3:
                std::cout << "Enter Static IP Address: ";
                std::cin >> ipAddress;
                std::cout << "Enter Subnet Mask: ";
                std::cin >> subnetMask;
                std::cout << "Enter Gateway: ";
                std::cin >> gateway;
                ipManager.setStaticIP(ipAddress, subnetMask, gateway);
                break;
            case 4:
                ipManager.enableDHCP();
                break;
            case 5:
                std::cout << "Enter Primary DNS: ";
                std::cin >> dns1;
                std::cout << "Enter Secondary DNS: ";
                std::cin >> dns2;
                ipManager.changeDNSServers(dns1, dns2);
                break;
            case 6:
                ipManager.resetDNS();
                break;
            case 7:
                std::cout << "Exiting..." << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void runCLI() {
    INetworkBackend* backend = CreatePlatformBackend();
    IPManager ipManager(backend);
    handleUserInput(ipManager);
    delete backend;
}