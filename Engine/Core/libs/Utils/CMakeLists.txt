cmake_minimum_required(VERSION 3.16)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE INTERNAL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE INTERNAL "" FORCE)

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
endif()

if (ANDROID_NDK)
    set(ASSIMP_BUILD_ZLIB OFF CACHE INTERNAL "" FORCE)
else()
    set(ASSIMP_BUILD_ZLIB ON CACHE INTERNAL "" FORCE)
endif()

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
add_subdirectory(libs/FQHSA)

if (SR_TRACY_ENABLE)
    add_subdirectory(libs/tracy)
endif()

if (SR_UTILS_STATIC_LIBRARY)
    add_library(Utils STATIC cxx/ICU.cxx cxx/Utils.cxx cxx/ECS.cxx cxx/World.cxx cxx/Platform.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Utils SHARED cxx/ICU.cxx cxx/Utils.cxx cxx/ECS.cxx cxx/World.cxx cxx/Platform.cxx)
    add_library(Utils::lib ALIAS Utils)
endif()

if (UNIX AND NOT APPLE)
    target_link_libraries(Utils ${X11_LIBRARIES})
    target_include_directories(Utils PUBLIC ${X11_INCLUDE_DIR})
endif()

if (ANDROID_NDK)
    target_link_libraries(Utils assimp)
else()
	target_link_libraries(Utils nfd assimp)
endif()

if (SR_TRACY_ENABLE)
    target_link_libraries(Utils tracy)
endif()

if (MSVC)
    target_compile_options(Utils PUBLIC /openmp)
endif()

target_link_libraries(Utils Fast-Quick-Hull)

target_include_directories(Utils PUBLIC inc)
target_include_directories(Utils PUBLIC libs)
target_include_directories(Utils PUBLIC libs/assimp/include)
target_include_directories(Utils PUBLIC libs/glm)
target_include_directories(Utils PUBLIC libs/FQHSA/header)

# --------------------------------------------------------------------------------------

if (SR_ICU)
    target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include/icu)
endif()

# --------------------------------------------------------------------------------------

if (SR_TRACY_ENABLE)
    target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include/tracy/tracy)
    target_include_directories(Utils PUBLIC libs/tracy/tracy)
endif()

# --------------------------------------------------------------------------------------

set(SR_UTILS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SR_UTILS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFiles.cmake)

add_custom_target(CopyUtilsFiles)
add_custom_command(TARGET CopyUtilsFiles
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DSR_UTILS_SOURCE_DIR=${SR_UTILS_SOURCE_DIR}
        -DSR_UTILS_BINARY_DIR=${SR_UTILS_BINARY_DIR}
        -DSR_ICU=${SR_ICU}
        -DSR_TRACY_ENABLE=${SR_TRACY_ENABLE}
        -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFiles.cmake"
    COMMENT "SpaRcle Engine: Copy utils source files to build directory"
)

add_dependencies(${PROJECT_NAME} CopyUtilsFiles)
