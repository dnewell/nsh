cmake_minimum_required(VERSION 3.3)
project(nsh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(nsh ${SOURCE_FILES})