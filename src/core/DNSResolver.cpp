#include "../include/DNSResolver.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <iostream>

bool DNSResolver::ResolveHostname(const std::string& hostname, std::vector<std::string>& outIps) {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        return false;
    }
#endif
    struct addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo* result = nullptr;
    int rc = getaddrinfo(hostname.c_str(), nullptr, &hints, &result);
    if (rc != 0) {
#ifdef _WIN32
        WSACleanup();
#endif
        return false;
    }

    for (struct addrinfo* rp = result; rp != nullptr; rp = rp->ai_next) {
        char addrStr[INET6_ADDRSTRLEN] = {0};
        void* addrPtr = nullptr;
        if (rp->ai_family == AF_INET) {
            struct sockaddr_in* sa = (struct sockaddr_in*)rp->ai_addr;
            addrPtr = &(sa->sin_addr);
        } else if (rp->ai_family == AF_INET6) {
            struct sockaddr_in6* sa6 = (struct sockaddr_in6*)rp->ai_addr;
            addrPtr = &(sa6->sin6_addr);
        }
        if (addrPtr) {
            inet_ntop(rp->ai_family, addrPtr, addrStr, sizeof(addrStr));
            outIps.emplace_back(addrStr);
        }
    }

    freeaddrinfo(result);
#ifdef _WIN32
    WSACleanup();
#endif
    return !outIps.empty();
}

bool DNSResolver::ReverseLookup(const std::string& ip, std::string& outName) {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        return false;
    }
#endif
    struct sockaddr_storage sa{};
    socklen_t saLen = 0;
    char host[NI_MAXHOST] = {0};

    if (inet_pton(AF_INET, ip.c_str(), &(((struct sockaddr_in*)&sa)->sin_addr))) {
        sa.ss_family = AF_INET;
        saLen = sizeof(struct sockaddr_in);
    } else if (inet_pton(AF_INET6, ip.c_str(), &(((struct sockaddr_in6*)&sa)->sin6_addr))) {
        sa.ss_family = AF_INET6;
        saLen = sizeof(struct sockaddr_in6);
    } else {
#ifdef _WIN32
        WSACleanup();
#endif
        return false;
    }

    int rc = getnameinfo((struct sockaddr*)&sa, saLen, host, sizeof(host), nullptr, 0, NI_NAMEREQD);
    if (rc != 0) {
#ifdef _WIN32
        WSACleanup();
#endif
        return false;
    }

    outName = host;
#ifdef _WIN32
    WSACleanup();
#endif
    return true;
}
