#pragma once

#include <string>

// Forward declaration to avoid including IPManager.h here
class IPManager;

void displayMenu();
void handleUserInput(IPManager& ipManager);
void runCLI();