#include "BackendFactory.h"
#include "IPManager.h"
#include "cli.h"
#include "DNSResolver.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

void displayMenu() {
    cout << "Mini IP Command Tool" << endl;
    cout << "1. View Current IP Configuration" << endl;
    cout << "2. DNS Resolver (resolve hostname / reverse lookup)" << endl;
    cout << "3. Set Static IP Address" << endl;
    cout << "4. Enable DHCP" << endl;
    cout << "5. Change DNS Servers" << endl;
    cout << "6. Reset/Flush DNS" << endl;
    cout << "7. Exit" << endl;
}

void handleUserInput(IPManager& ipManager) {
    int choice;
    string ipAddress, subnetMask, gateway, dns1, dns2;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ipManager.viewCurrentConfiguration();
                break;
            case 2: {
                cout << "DNS Resolver:\n1) Resolve hostname\n2) Reverse lookup (IP to name)\nChoose: ";
                int sub;
                cin >> sub;
                if (sub == 1) {
                    cout << "Enter hostname: ";
                    string host;
                    cin >> host;
                    vector<string> ips;
                    if (DNSResolver::ResolveHostname(host, ips)) {
                        cout << "Resolved IPs:\n";
                        for (auto &a : ips) cout << "  " << a << endl;
                    } else {
                        cout << "Resolution failed for " << host << endl;
                    }
                } else if (sub == 2) {
                    cout << "Enter IP address: ";
                    string ip;
                    cin >> ip;
                    string name;
                    if (DNSResolver::ReverseLookup(ip, name)) {
                        cout << "Hostname: " << name << endl;
                    } else {
                        cout << "Reverse lookup failed for " << ip << endl;
                    }
                } else {
                    cout << "Invalid selection." << endl;
                }
                break;
            }
            case 3:
                cout << "Enter Static IP Address: ";
                cin >> ipAddress;
                cout << "Enter Subnet Mask: ";
                cin >> subnetMask;
                cout << "Enter Gateway: ";
                cin >> gateway;
                ipManager.setStaticIP(ipAddress, subnetMask, gateway);
                break;
            case 4:
                ipManager.enableDHCP();
                break;
            case 5:
                cout << "Enter Primary DNS: ";
                cin >> dns1;
                cout << "Enter Secondary DNS: ";
                cin >> dns2;
                ipManager.changeDNSServers(dns1, dns2);
                break;
            case 6:
                ipManager.resetDNS();
                break;
            case 7:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void runCLI() {
    INetworkBackend* backend = CreatePlatformBackend();
    IPManager ipManager(backend);
    handleUserInput(ipManager);
    delete backend;
}