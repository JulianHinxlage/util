cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(FLAGS "-pthread -Wall -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

project(util)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

add_library(util STATIC ${SOURCES} ${HEADERS})
target_include_directories(util PUBLIC src)
