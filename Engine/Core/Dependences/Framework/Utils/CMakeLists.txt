cmake_minimum_required(VERSION 3.16)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

if (UTILS_STATIC_LIBRARY)
    add_library(Utils STATIC Utils.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Utils SHARED Utils.cxx)
    add_library(Utils::lib ALIAS Utils)
endif()

target_include_directories(Utils PUBLIC inc)
