#include "WindowsNetwork.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include <iostream>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void WindowsNetwork::viewCurrentConfiguration() {
    // Initialize Winsock because getnameinfo requires it on some platforms
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        return;
    }

    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_UNSPEC; // both IPv4 and IPv6
    ULONG outBufLen = 15000;
    PIP_ADAPTER_ADDRESSES adapters = (PIP_ADAPTER_ADDRESSES)malloc(outBufLen);
    if (!adapters) {
        cerr << "Memory allocation failed for adapter addresses" << endl;
        WSACleanup();
        return;
    }

    ULONG ret = GetAdaptersAddresses(family, flags, nullptr, adapters, &outBufLen);
    if (ret == ERROR_BUFFER_OVERFLOW) {
        free(adapters);
        adapters = (PIP_ADAPTER_ADDRESSES)malloc(outBufLen);
        if (!adapters) {
            cerr << "Memory allocation failed for adapter addresses" << endl;
            WSACleanup();
            return;
        }
        ret = GetAdaptersAddresses(family, flags, nullptr, adapters, &outBufLen);
    }

    if (ret == NO_ERROR) {
        for (PIP_ADAPTER_ADDRESSES adapter = adapters; adapter != nullptr; adapter = adapter->Next) {
            // Print adapter friendly name (wide string)
            if (adapter->FriendlyName) {
                wcout << L"Adapter: " << adapter->FriendlyName << endl;
            } else if (adapter->AdapterName) {
                cout << "Adapter: " << adapter->AdapterName << endl;
            }

            // Iterate unicast addresses
            for (PIP_ADAPTER_UNICAST_ADDRESS unicast = adapter->FirstUnicastAddress; unicast != nullptr; unicast = unicast->Next) {
                char addrBuf[INET6_ADDRSTRLEN] = {0};
                int rc = getnameinfo(unicast->Address.lpSockaddr,
                                     (DWORD)unicast->Address.iSockaddrLength,
                                     addrBuf, sizeof(addrBuf),
                                     nullptr, 0, NI_NUMERICHOST);
                if (rc == 0) {
                    cout << "  IP Address: " << addrBuf << endl;
                }
            }

            cout << endl;
        }
    } else {
        cerr << "GetAdaptersAddresses() failed with error: " << ret << endl;
    }

    if (adapters) free(adapters);
    WSACleanup();
}

void WindowsNetwork::setStaticIP(const string& ipAddress, const string& subnetMask, const string& gateway) {
    cout << "Setting static IP to " << ipAddress << " with subnet mask " << subnetMask
              << " and gateway " << gateway << " (Windows)." << endl;
}

void WindowsNetwork::enableDHCP() {
    cout << "Enabling DHCP (Windows)." << endl;
}

void WindowsNetwork::changeDNSServers(const string& primaryDNS, const string& secondaryDNS) {
    cout << "Changing DNS servers to Primary: " << primaryDNS
              << " and Secondary: " << secondaryDNS << " (Windows)." << endl;
}

void WindowsNetwork::resetFlushDNS() {
    cout << "Resetting/flushing DNS (Windows)." << endl;
}