cmake_minimum_required(VERSION 3.16)
project(FbxLoader)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/tinyobjloader)

add_library(FbxLoader STATIC
        src/FbxLoader/Loader.cpp
        src/FbxLoader/Parser.cpp
        src/FbxLoader/Fbx.cpp
        )

target_link_libraries(FbxLoader TinyObjLoader)

target_include_directories(FbxLoader PUBLIC inc libs/tinyobjloader)
