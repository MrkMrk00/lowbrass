cmake_minimum_required(VERSION 3.10)

project(lowbrass VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

