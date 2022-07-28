cmake_minimum_required(VERSION 3.16)
project(SREngine)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fconcepts-ts")

set(SR_UTILS_STATIC_LIBRARY ON)
set(SR_AUDIO_STATIC_LIBRARY ON)
set(SR_PHYSICS_STATIC_LIBRARY ON)
set(EVO_VULKAN_STATIC_LIBRARY ON)

add_subdirectory(Engine)
