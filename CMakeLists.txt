cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 20)

set(SR_UTILS_STATIC_LIBRARY ON)
set(EVOVULKAN_STATIC_LIBRARY OFF)

add_subdirectory(Engine)
