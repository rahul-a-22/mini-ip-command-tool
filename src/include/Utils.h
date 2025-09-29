#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <fstream>

// Utility functions
namespace Utils {
    void logAction(const std::string& action);
    bool validateIPAddress(const std::string& ip);
    bool validateSubnetMask(const std::string& subnet);
    bool validateDNS(const std::string& dns);
}

#endif // UTILS_H