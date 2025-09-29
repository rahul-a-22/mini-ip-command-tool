#include "BackendFactory.h"

#ifdef _WIN32
#include "../backend/windows/WindowsNetwork.h"
INetworkBackend* CreatePlatformBackend() { return new WindowsNetwork(); }
#else
#include "../backend/linux/LinuxNetwork.h"
INetworkBackend* CreatePlatformBackend() { return new LinuxNetwork(); }
#endif
