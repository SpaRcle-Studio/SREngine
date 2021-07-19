cmake_minimum_required(VERSION 3.16)
project(Editor)

set(CMAKE_CXX_STANDARD 20)

add_library(Editor SHARED Editor.cpp)
