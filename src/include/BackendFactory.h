#pragma once

#include "INetworkBackend.h"

// Returns a pointer to a platform-specific INetworkBackend implementation.
// Caller owns the returned pointer and must delete it.
INetworkBackend* CreatePlatformBackend();
