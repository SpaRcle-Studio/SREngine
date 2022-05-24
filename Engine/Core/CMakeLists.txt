cmake_minimum_required(VERSION 3.16)
project(Core)

add_subdirectory(Dependences/Framework)

set(CORE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(Core STATIC ${CORE_ROOT_DIR}/Core.cxx)

target_link_libraries(Core Framework)

target_include_directories(Core PUBLIC ${CORE_ROOT_DIR}/inc)