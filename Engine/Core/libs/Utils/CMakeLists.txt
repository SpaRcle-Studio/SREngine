cmake_minimum_required(VERSION 3.16)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF)

add_subdirectory(libs/nativefiledialog)
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


target_link_libraries(Utils assimp nfd)

target_include_directories(Utils PUBLIC inc)
target_include_directories(Utils PUBLIC libs)
target_include_directories(Utils PUBLIC libs/assimp/include)

# --------------------------------------------------------------------------------------

list(APPEND SR_UTILS_ALL_HEADERS inc/Utils/)

foreach(SR_UTILS_HEADER ${SR_UTILS_ALL_HEADERS})
    file(COPY ${SR_UTILS_HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/Utils)
endforeach()