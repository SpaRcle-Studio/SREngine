cmake_minimum_required(VERSION 3.16...3.16.2)
project(SREngine)

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "SpaRcle Engine supports only x64 systems!")
endif()

message(${CMAKE_VERSION})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_CXX_STANDARD 20)

# add_subdirectory(Engine)

add_subdirectory(Engine/Core)

add_executable(SREngine main.cpp)