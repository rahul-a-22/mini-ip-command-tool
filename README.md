# Mini IP Command Tool

## Overview
The Mini IP Command Tool is a cross-platform command-line application to manage IP/network configuration on Windows and Linux. It provides a small interactive CLI to view current IP settings, resolve hostnames, set static IPs, enable DHCP, change DNS servers, and reset/flush DNS.

## Features
- View current IP configuration (enumerates adapters and addresses)
- DNS resolver: resolve hostname → IPs, and reverse lookup IP → hostname
- Set a static IP address (platform-specific)
- Enable DHCP (platform-specific)
- Change DNS servers (platform-specific)
- Reset/flush DNS (platform-specific)

## CLI Menu (default)
1. View Current IP Configuration
2. DNS Resolver (resolve hostname / reverse lookup)
3. Set Static IP Address
4. Enable DHCP
5. Change DNS Servers
6. Reset/Flush DNS
7. Exit

## Project Structure
```
mini-ip-tool
├── src
│   ├── main.cpp
│   ├── cli
│   │   ├── cli.cpp
│   │   └── cli.h
│   ├── include
│   │   ├── IPManager.h
│   │   ├── INetworkBackend.h
│   │   ├── DNSResolver.h
│   │   └── BackendFactory.h
│   ├── core
│   │   ├── IPManager.cpp
│   │   ├── BackendFactory.cpp
│   │   └── DNSResolver.cpp
│   └── backend
│       ├── linux
│       │   ├── LinuxNetwork.h
│       │   └── LinuxNetwork.cpp
│       └── windows
│           ├── WindowsNetwork.h
│           └── WindowsNetwork.cpp
├── tests (optional)
│   └── test_ipmanager.cpp
├── CMakeLists.txt
├── README.md
└── LICENSE
```

## Requirements
- C++17
- CMake >= 3.10 (tested with 3.31.6-msvc9)
- Ninja or another generator supported by CMake
- On Windows: Visual Studio / MSVC toolchain
- (Optional) GTest for running tests

## Build Instructions
From the repository root:

- Configure and generate build files:
  - Recommended (out-of-source build):
    ```
    cmake -S . -B build
    ```
- Build:
  ```
  cmake --build build
  ```
- Run the executable:
  - Windows: `build\\mini-ip-tool.exe`
  - Linux/macOS: `./build/mini-ip-tool`

Notes:
- Tests are optional and disabled by default. Enable with `-DBUILD_TESTS=ON` when running CMake and ensure GTest is available.

## Usage
Run the program and follow the interactive menu. Use option 2 to use the DNS resolver:
- Choose `2`, then `1` to resolve a hostname to IPs.
- Choose `2`, then `2` to reverse-lookup an IP to a hostname.

## Platform notes
- Platform-specific operations (set IP, DHCP, DNS changes, flush) are implemented in backend modules under `src/backend/windows` and `src/backend/linux`. Some actions may require elevated privileges (Administrator/root).

## Contributing
Contributions are welcome. Open issues or submit pull requests for features, bug fixes, or tests.

## License
This project is licensed under the MIT License. See the LICENSE file for details.