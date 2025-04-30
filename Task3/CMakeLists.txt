cmake_minimum_required(VERSION 3.24)
project(Task3 LANGUAGES CXX)

# Global settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Searching for dependencies
find_package(GTest REQUIRED)

# Main executable
add_executable(${PROJECT_NAME} main.cpp)

# Tests
enable_testing()
add_executable(${PROJECT_NAME}-ut testy.cpp)
target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::GTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
