#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void logAction(const string& action) {
    ofstream logFile("logs/actions.log", ios_base::app);
    if (logFile.is_open()) {
        time_t now = time(nullptr);
        logFile << ctime(&now) << ": " << action << endl;
        logFile.close();
    } else {
        cerr << "Unable to open log file." << endl;
    }
}

bool validateIPAddress(const string& ip) {
    // Simple validation for IPv4 format
    string octet;
    int dotCount = 0;
    for (char c : ip) {
        if (c == '.') {
            if (octet.empty() || stoi(octet) > 255) return false;
            dotCount++;
            octet.clear();
        } else if (isdigit(c)) {
            octet += c;
        } else {
            return false;
        }
    }
    return dotCount == 3 && !octet.empty() && stoi(octet) <= 255;
}