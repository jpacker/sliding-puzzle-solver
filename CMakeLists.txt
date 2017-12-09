cmake_minimum_required(VERSION 3.9)

project(sliding_puzzle_solver LANGUAGES CXX)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE 
	"${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -march=native")

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)

set(SOLVER_SOURCES ${SRC_DIR}/solver.cpp)
set(SOLVER_HEADERS ${INCLUDE_DIR}/solver.hpp)

include(CTest)
enable_testing()
add_subdirectory(test)

set(BINARY_SOURCES src/main.cpp)

add_executable(sliding_puzzle_solver 
	${SOLVER_SOURCES} ${SOLVER_HEADERS} ${BINARY_SOURCES})
