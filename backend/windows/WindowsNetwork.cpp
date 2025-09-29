#include "WindowsNetwork.h"
#include <winsock2.h>
#include <ws2tcpip.h>

// Link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

WindowsNetwork::WindowsNetwork() {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        // Handle error
    }
}

WindowsNetwork::~WindowsNetwork() {
    WSACleanup();
}

// Example method: Get local IP address
std::string WindowsNetwork::GetLocalIPAddress() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        return "";
    }

    struct addrinfo hints = {}, *info = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, nullptr, &hints, &info) != 0) {
        return "";
    }

    std::string ip;
    for (auto p = info; p != nullptr; p = p->ai_next) {
        sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(p->ai_addr);
        ip = inet_ntoa(addr->sin_addr);
        break;
    }
    freeaddrinfo(info);
    return ip;
}