set(CTest OFF)

include(CTest)

enable_testing()

# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Add the test executable
add_executable(test_ipmanager test_ipmanager.cpp)

# Link the test executable with the necessary libraries
target_link_libraries(test_ipmanager PRIVATE your_project_libs)

# Add tests
add_test(NAME TestIPManager COMMAND test_ipmanager)