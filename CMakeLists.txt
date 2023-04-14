cmake_minimum_required(VERSION 3.16...3.16.2)
project(SREngine)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Engine)
