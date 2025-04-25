cmake_minimum_required(VERSION 3.10)

project(task3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -std=c++20")
set(CMAKE_CXX_STANDARD 20)
file(GLOB sources "main.cpp")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp)

if(APPLE)
	target_link_libraries(${PROJECT_NAME} "-framework IOkit")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
