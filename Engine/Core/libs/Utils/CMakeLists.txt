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
add_subdirectory(libs/fmt)

if (SR_TRACY_ENABLE)
    add_subdirectory(libs/tracy)
endif()


list(APPEND SR_UTILS_LINK_LIBRARIES cxx/ICU.cxx)
list(APPEND SR_UTILS_LINK_LIBRARIES cxx/Utils.cxx)
list(APPEND SR_UTILS_LINK_LIBRARIES cxx/ECS.cxx)
list(APPEND SR_UTILS_LINK_LIBRARIES cxx/World.cxx)
list(APPEND SR_UTILS_LINK_LIBRARIES cxx/Platform.cxx)
list(APPEND SR_UTILS_LINK_LIBRARIES cxx/Types.cxx)
list(APPEND SR_UTILS_LINK_LIBRARIES cxx/Common.cxx)

define_property(GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
set_property(GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES "")

macro(SR_UTILS_INCLUDE_DIRECTORIES_APPEND var)
    set_property(GLOBAL APPEND PROPERTY SR_UTILS_INCLUDE_DIRECTORIES "${var}")
endmacro(SR_UTILS_INCLUDE_DIRECTORIES_APPEND)

SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_BINARY_DIR}/include)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_BINARY_DIR}/libs)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_BINARY_DIR}/libs/assimp/include)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_SOURCE_DIR}/inc)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_SOURCE_DIR}/libs)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/include)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_SOURCE_DIR}/libs/FQHSA/header)
SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_SOURCE_DIR}/libs/fmt/include)

if (SR_ICU)
    SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_BINARY_DIR}/include/icu)
endif()

if (SR_TRACY_ENABLE)
    SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_BINARY_DIR}/include/tracy/tracy)
    SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${CMAKE_CURRENT_SOURCE_DIR}/libs/tracy/tracy)
endif()

if (UNIX)
    list(APPEND SR_UTILS_LINK_LIBRARIES src/Utils/Platform/LinuxStacktraceImpl.cpp)
endif ()

if (SR_UTILS_STATIC_LIBRARY)
    add_library(Utils STATIC ${SR_UTILS_LINK_LIBRARIES})

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Utils SHARED ${SR_UTILS_LINK_LIBRARIES})
    add_library(Utils::lib ALIAS Utils)
endif()

if (UNIX AND NOT APPLE)
    target_link_libraries(Utils ${X11_LIBRARIES})
    target_link_libraries(Utils ${X11_Xrandr_LIB})
    SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${X11_Xrandr_INCLUDE_PATH})

    target_link_libraries(Utils ${X11_xcb_randr_LIB})
    SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${X11_xcb_randr_INCLUDE_PATH})

    target_link_libraries(Utils bfd)
    SR_UTILS_INCLUDE_DIRECTORIES_APPEND(${LIBBFD_INCLUDE_DIRS})
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

target_link_libraries(Utils Fast-Quick-Hull fmt)

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
message("SpaRcle utils include directories: ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT}")
message("SpaRcle utils include directories: ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT}")
target_include_directories(Utils PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})

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
