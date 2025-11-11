cmake_minimum_required(VERSION 3.16)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT MSVC AND NOT ANDROID_NDK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif()

project(Audio)

SR_COMMON_GENERATE_BUILD_SOURCES(${PROJECT_SOURCE_DIR})
SR_COMMON_GET_SOURCES(Audio)

set(CMAKE_CXX_STANDARD 20)

option(SR_AUDIO_DLL_EXPORTS "" ON)

add_definitions(
    -DMODPLUG_STATIC
    -DFLAC__NO_DLL
    -DAL_LIBTYPE_STATIC
)

set(LIBTYPE STATIC)

set(ALSOFT_INSTALL_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(ALSOFT_BUILD_IMPORT_LIB OFF CACHE INTERNAL "" FORCE)
set(ALSOFT_INSTALL_UTILS OFF CACHE INTERNAL "" FORCE)
set(ALSOFT_UTILS OFF CACHE INTERNAL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE INTERNAL "" FORCE)

if (ANDROID_NDK)
    set(ALSOFT_LIKELY_UNLIKELY OFF CACHE INTERNAL "" FORCE)
endif()

set(LIBTYPE STATIC)

if (NOT SR_EMSCRIPTEN)
    add_subdirectory(libs/OpenAL)
    add_subdirectory(libs/libmodplug)

    if(MSVC)
        target_compile_options(modplug PRIVATE "/wd5033;")
    endif()
endif()

if (SR_AUDIO_STATIC_LIBRARY)
    add_library(Audio STATIC ${Audio_SOURCES})
else()
    add_library(Audio SHARED ${Audio_SOURCES})
    add_library(Audio::lib ALIAS Audio)

    if (UNIX)
        target_compile_options(Audio PRIVATE -fPIC)
    endif()

    target_link_libraries(Audio PUBLIC Utils)

    SR_COPY_SHARED_MODULE_TO_EXECUTABLE_FOLDER(Audio)
    SR_COPY_STATIC_LIBRARY_TO_LIBRARY_FOLDER(Audio)
endif()

if (SR_AUDIO_DLL_EXPORTS)
    message("Audio will be using DLL exports")
    target_compile_definitions(Audio PUBLIC SR_AUDIO_DLL_EXPORTS)
endif()

if (NOT SR_EMSCRIPTEN)
    target_link_libraries(Audio PUBLIC OpenAL)
    target_include_directories(Audio PUBLIC libs/OpenAL/include)

    target_link_libraries(Audio PUBLIC modplug)
    target_include_directories(Audio PUBLIC libs/libmodplug/src)
endif()

target_include_directories(Audio PUBLIC inc)
target_include_directories(Audio PUBLIC libs)

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
target_include_directories(Audio PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})
