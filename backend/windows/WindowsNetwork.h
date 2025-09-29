#pragma once

#include <string>

class WindowsNetwork {
public:
    WindowsNetwork();
    ~WindowsNetwork();

    // Example method to get the local IP address
    std::string GetLocalIPAddress();
};