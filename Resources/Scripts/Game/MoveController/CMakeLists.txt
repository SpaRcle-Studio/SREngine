cmake_minimum_required(VERSION 3.16)
project(MoveController)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_INIT "-Werror -Wall -Wextra -Wpedantic -Wattributes")

add_library(MoveController SHARED MoveController.cpp)
