cmake_minimum_required(VERSION 3.16)
project(Utils)

set(CMAKE_CXX_STANDARD 20)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF)

add_subdirectory(libs/glm)
add_subdirectory(libs/assimp)

if (SR_UTILS_STATIC_LIBRARY)
    add_library(Utils STATIC Utils.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Utils SHARED Utils.cxx)
    add_library(Utils::lib ALIAS Utils)
endif()

target_link_libraries(Utils assimp)

target_include_directories(Utils PUBLIC inc)
target_include_directories(Utils PUBLIC libs)
target_include_directories(Utils PUBLIC libs/assimp/include)
