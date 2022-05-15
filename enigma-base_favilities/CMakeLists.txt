cmake_minimum_required(VERSION 2.6)
project(enigma)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB_RECURSE ${CMAKE_PROJECT_NAME}_sources src/*.cpp)
file(GLOB_RECURSE ${CMAKE_PROJECT_NAME}_headers src/*.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_sources})
