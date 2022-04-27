cmake_minimum_required (VERSION 2.9)

project (TER)

set(CPLEX_HOME "/home/lucas/Desktop/Cplex/concert")

set(CPLEX_INCLUDE_DIR "${CPLEX_HOME}/include")
message(STATUS "CPLEX_INCLUDE_DIR : ${CPLEX_INCLUDE_DIR}")

set(CPLEX_LIBRARY "${CPLEX_HOME}/lib/x86-64_linux/static_pic/libconcert.a")
message(STATUS "CPLEX_LIBRARY : ${CPLEX_LIBRARY}")

include_directories(${CPLEX_INCLUDE_DIR} include)

file(GLOB_RECURSE SRCS src/*.cpp)

message(STATUS "SRCS : ${SRCS}")

add_executable(TER.exe ${SRCS})

target_link_libraries(TER.exe ${CPLEX_LIBRARY})