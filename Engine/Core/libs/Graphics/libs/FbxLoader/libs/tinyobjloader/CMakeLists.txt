cmake_minimum_required(VERSION 3.16)
project(FbxLoader)

set(CMAKE_CXX_STANDARD 20)

add_library(TinyObjLoader STATIC
        src/tiny_obj_loader.cc
        )

target_include_directories(TinyObjLoader PUBLIC inc)
