cmake_minimum_required(VERSION 3.16)
project(Core)

set(CORE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Core STATIC
        ${CORE_ROOT_DIR}/src/EvoScriptAPI.cpp
        ${CORE_ROOT_DIR}/src/Engine.cpp
        ${CORE_ROOT_DIR}/src/GUI/Canvas.cpp
        )

target_link_libraries(Core Framework)

target_include_directories(Core
        PUBLIC ${CORE_ROOT_DIR}/inc
        )