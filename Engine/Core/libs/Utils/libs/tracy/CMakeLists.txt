cmake_minimum_required(VERSION 3.16)

project(tracy)

add_library(tracy STATIC TracyClient.cpp)

target_include_directories(tracy PUBLIC tracy)