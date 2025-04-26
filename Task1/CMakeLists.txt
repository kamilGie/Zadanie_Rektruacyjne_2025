cmake_minimum_required(VERSION 3.10)

project(Task1)

# Ustaw standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ustawienia flagi kompilatora
if(MSVC)
  # dla Visual Studio
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /std:c++20")
else()
  # dla gcc/clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++20")
endif()

# Output plików wykonywalnych bez Debug/Release katalogów
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Aplikacja
set(sources src/Application.cpp)
add_executable(${PROJECT_NAME} main.cpp ${sources})

# Plik compile_commands.json dla Neovim LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Testy jednostkowe
add_executable(${PROJECT_NAME}-ut testy.cpp ${sources})
target_link_libraries(${PROJECT_NAME}-ut GTest::gtest_main)

# Autoodkrywanie testów
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
