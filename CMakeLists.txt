cmake_minimum_required (VERSION 2.9)

project (TER)

set(GUROBI_ROOT "/opt/gurobi951/linux64/")
set(GUROBI_INCLUDE_DIR "${GUROBI_ROOT}include")
message(STATUS "GUROBI_INCLUDE_DIR : ${GUROBI_INCLUDE_DIR}")


set(GUROBI_LIBRARY_CPLUS "${GUROBI_ROOT}lib/libgurobi_c++.a")
set(GUROBI_LIBRARY "${GUROBI_ROOT}lib/libgurobi95.so")
set(GUROBI_LIBRARIES ${GUROBI_LIBRARY_CPLUS} ${GUROBI_LIBRARY})
message(STATUS "GUROBI_LIBRARIES : ${GUROBI_LIBRARIES}")

include_directories(${GUROBI_INCLUDE_DIR} include)
file(GLOB_RECURSE SRCS src/*.cpp)

message(STATUS "SRCS : ${SRCS}")

add_executable(TER.exe ${SRCS})

target_link_libraries(TER.exe ${GUROBI_LIBRARIES})