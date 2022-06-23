cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 20)

set(SR_UTILS_STATIC_LIBRARY ON)
set(EVO_VULKAN_STATIC_LIBRARY ON)

add_subdirectory(Engine)
