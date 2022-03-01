cmake_minimum_required (VERSION 2.6)

project (TER)

include_directories(include)
file(GLOB_RECURSE SRCS src/*.cpp)

message(STATUS "SRCS : ${SRCS}")

add_executable(v0 ${SRCS})