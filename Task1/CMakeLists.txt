cmake_minimum_required(VERSION 3.24)
project(Task1)

# Ustaw standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Główna aplikacja
set(SOURCES src/Application.cpp src/SearchBar.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

enable_testing()

# Find GTest via Conan (don't use find_package directly)
find_package(GTest REQUIRED CONFIG)

# Test executable
add_executable(${PROJECT_NAME}-ut testy.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::GTest GTest::gtest_main)

# Autoodkrywanie testów
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
