cmake_minimum_required(VERSION 3.13)
project(cpp-itertools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS}")

find_package(cppcoro CONFIG REQUIRED)

add_executable(cpp-itertools example.cpp)
target_link_libraries(cpp-itertools PRIVATE cppcoro)
target_include_directories(cpp-itertools PUBLIC .)

set(CMAKE_BUILD_TYPE Release)