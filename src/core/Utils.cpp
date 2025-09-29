#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

void logAction(const std::string& action) {
    std::ofstream logFile("logs/actions.log", std::ios_base::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        logFile << std::ctime(&now) << ": " << action << std::endl;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}

bool validateIPAddress(const std::string& ip) {
    // Simple validation for IPv4 format
    std::string octet;
    int dotCount = 0;
    for (char c : ip) {
        if (c == '.') {
            if (octet.empty() || std::stoi(octet) > 255) return false;
            dotCount++;
            octet.clear();
        } else if (isdigit(c)) {
            octet += c;
        } else {
            return false;
        }
    }
    return dotCount == 3 && !octet.empty() && std::stoi(octet) <= 255;
}