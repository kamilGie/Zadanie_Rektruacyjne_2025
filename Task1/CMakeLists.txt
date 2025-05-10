cmake_minimum_required(VERSION 3.24)
project(Task1 LANGUAGES CXX)

# Globalne ustawienia
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Wymuszam użycie nowszego GCC na Ubuntu
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.0)
		message(FATAL_ERROR "Wymagany GCC >= 13. Zainstaluj: sudo apt install gcc-13 g++-13")
	endif()
	add_compile_options(-fconcepts)
endif()

set(SOURCES src/Application.cpp src/SearchBar.cpp)

# Wyszukiwanie zależności
find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

# Główny plik wykonywalny
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} boost::boost)

# Testy
enable_testing()
add_executable(${PROJECT_NAME}-ut testy.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME}-ut PRIVATE GTest::GTest GTest::gtest_main GTest::gmock_main boost::boost)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
