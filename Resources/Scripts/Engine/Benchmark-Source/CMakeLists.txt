cmake_minimum_required(VERSION 3.16)
project(Benchmark)

set(CMAKE_CXX_STANDARD 20)

add_library(Engine SHARED Benchmark.cpp)
