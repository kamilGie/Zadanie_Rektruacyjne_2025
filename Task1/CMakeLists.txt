cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(Task1)

set(SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)
