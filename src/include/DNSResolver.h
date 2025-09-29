#pragma once

#include <string>
#include <vector>

class DNSResolver {
public:
    // Resolve hostname to IP addresses (IPv4 and IPv6). Returns true on success and fills outIps.
    static bool ResolveHostname(const std::string& hostname, std::vector<std::string>& outIps);

    // Reverse lookup: IP to hostname. Returns true on success and fills outName.
    static bool ReverseLookup(const std::string& ip, std::string& outName);
};
