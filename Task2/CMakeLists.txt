cmake_minimum_required(VERSION 3.15)

project(Task2)

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

# Plik compile_commands.json dla LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Aplikacja
set(sources src/Visualisation.cpp src/Application.cpp)
add_executable(${PROJECT_NAME} main.cpp ${sources})

# GoogleTest
include(FetchContent)
FetchContent_Declare(
		googletest
		URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
						DOWNLOAD_EXTRACT_TIMESTAMP
						TRUE)
set(gtest_force_shared_crt
				ON
				CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# raylib
FetchContent_Declare(
		raylib
		URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
						DOWNLOAD_EXTRACT_TIMESTAMP
						TRUE)
set(BUILD_EXAMPLES
				OFF
				CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)
target_link_libraries(${PROJECT_NAME} raylib)

if(APPLE)
	target_link_libraries(${PROJECT_NAME} "-framework IOkit")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Enable testing
enable_testing()

# Testy jednostkowe
add_executable(${PROJECT_NAME}-ut testy.cpp ${sources})
target_link_libraries(${PROJECT_NAME}-ut GTest::gtest_main raylib)

# Autoodkrywanie testów
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
