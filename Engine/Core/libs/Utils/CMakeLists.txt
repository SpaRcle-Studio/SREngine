cmake_minimum_required(VERSION 3.16)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE INTERNAL "" FORCE)

set(ICU_PREBUILT_VERSION "69.1")

if (NOT ANDROID_NDK)
    add_subdirectory(libs/nativefiledialog)
else()
    #set(ASSIMP_ANDROID_JNIIOSYSTEM ON CACHE INTERNAL "" FORCE)
    #set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE INTERNAL "" FORCE)
    #set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE INTERNAL "" FORCE)
endif()

add_subdirectory(libs/glm)
add_subdirectory(libs/assimp)

if (SR_UTILS_STATIC_LIBRARY)
    add_library(Utils STATIC ICU.cxx Utils.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Utils SHARED ICU.cxx Utils.cxx)
    add_library(Utils::lib ALIAS Utils)
endif()

if (ANDROID_NDK)
    target_link_libraries(Utils assimp)
else()
	target_link_libraries(Utils nfd assimp)
endif()

if (MSVC)
    target_compile_options(Utils PUBLIC /openmp)
endif()

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include/icu)
target_include_directories(Utils PUBLIC inc)
target_include_directories(Utils PUBLIC libs)
target_include_directories(Utils PUBLIC libs/assimp/include)

# --------------------------------------------------------------------------------------

list(APPEND SR_UTILS_ALL_HEADERS inc/Utils/)

foreach(SR_UTILS_HEADER ${SR_UTILS_ALL_HEADERS})
    file(COPY ${SR_UTILS_HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/Utils)
endforeach()

# --------------------------------------------------------------------------------------

list(APPEND SR_UTILS_ICU_ALL_HEADERS libs/icu)

foreach(SR_UTILS_ICU_HEADER ${SR_UTILS_ICU_ALL_HEADERS})
    file(COPY ${SR_UTILS_ICU_HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include)
endforeach()