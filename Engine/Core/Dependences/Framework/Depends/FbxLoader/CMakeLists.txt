cmake_minimum_required(VERSION 3.16)
project(FbxLoader)

set(CMAKE_CXX_STANDARD 20)

add_library(FbxLoader STATIC
        src/FbxLoader/Loader.cpp
        src/FbxLoader/Parser.cpp
        )

target_include_directories(FbxLoader PUBLIC inc)
