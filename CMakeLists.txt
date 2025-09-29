cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(mini-ip-tool VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option to control building tests
option(BUILD_TESTS "Build unit tests" OFF)

# Source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Add the executable
add_executable(mini-ip-tool ${SOURCES})

# Platform-specific backend
if (WIN32)
    target_sources(mini-ip-tool PRIVATE src/backend/windows/WindowsNetwork.cpp)
elseif (UNIX)
    target_sources(mini-ip-tool PRIVATE src/backend/linux/LinuxNetwork.cpp)
endif()

# Include directories
target_include_directories(mini-ip-tool PRIVATE src/include src/backend/windows)

# Enable testing
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()