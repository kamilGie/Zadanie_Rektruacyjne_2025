cmake_minimum_required(VERSION 3.10)
project(NOVOMATIC-2025)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
		googletest
		URL https://github.com/google/googletest/archive/refs/heads/main.zip)
FetchContent_MakeAvailable(googletest)

add_subdirectory(Task1)
add_subdirectory(Task2)
add_subdirectory(Task3)
add_subdirectory(Tests)
