cmake_minimum_required(VERSION 2.8)
project(suffix_array)

set (CMAKE_CXX_COMPILER clang++)
set (CMAKE_CXX_FLAGS "-std=c++11  -W  -Wall")
set (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS} -O3)
set (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS} -g)

#add_library(suffix_array
# suffix_array.cpp
#)

add_executable(run_suffix_array
  main.cpp
)

