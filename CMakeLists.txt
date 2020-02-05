cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(FLAGS "-pthread -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

project(util)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
include_directories(src)


set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
add_library(util STATIC ${SOURCES} ${HEADERS})

project(utiltest)
link_directories(utiltest lib)
include_directories(src)
add_executable(utiltest src/main.cpp)
target_link_libraries(utiltest util)
