cmake_minimum_required(VERSION 3.16...3.16.2)
project(SREngine)

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "SpaRcle Engine supports only x64 systems!")
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Engine)
