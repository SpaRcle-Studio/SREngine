cmake_minimum_required(VERSION 3.16)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT MSVC AND NOT ANDROID_NDK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif()

project(Audio)

SR_COMMON_GENERATE_BUILD_SOURCES(${PROJECT_SOURCE_DIR})
SR_COMMON_GET_SOURCES(Audio)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SR_AUDIO_DLL_EXPORTS "" ON)
option(SR_AUDIO_USE_VORBIS "" ON)
option(SR_AUDIO_USE_FLAC "" ON)

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

add_subdirectory(libs/libmodplug)

if (NOT SR_EMSCRIPTEN)
    add_subdirectory(libs/OpenAL)

    if(MSVC)
        target_compile_options(modplug PRIVATE "/wd5033;")
    endif()
endif()

if (SR_AUDIO_USE_VORBIS OR SR_AUDIO_USE_FLAC)
    message("Audio will be built with OGG support")
    add_definitions(-DSR_AUDIO_USE_OGG)
    add_subdirectory(libs/ogg)

    if (UNIX)
        target_compile_options(ogg PRIVATE -fPIC)
    endif()
endif()

if (SR_AUDIO_USE_VORBIS)
    message("Audio will be built with VORBIS support")

    set(BUILD_SHARED_LIBS OFF CACHE BOOL "")

    add_definitions(-DSR_AUDIO_USE_VORBIS)
    add_subdirectory(libs/vorbis)

    if (UNIX)
        target_compile_options(vorbis PRIVATE -fPIC)
        target_compile_options(vorbisfile PRIVATE -fPIC)
    endif()
endif()

if (SR_AUDIO_USE_FLAC)
    message("Audio will be built with FLAC support")

    # Flac
    set(BUILD_CXXLIBS             OFF CACHE BOOL "")
    set(BUILD_PROGRAMS            OFF CACHE BOOL "")
    set(BUILD_EXAMPLES            OFF CACHE BOOL "")
    set(BUILD_TESTING             OFF CACHE BOOL "")
    set(BUILD_DOCS                OFF CACHE BOOL "")
    set(INSTALL_MANPAGES          OFF CACHE BOOL "")
    set(INSTALL_PKGCONFIG_MODULES OFF CACHE BOOL "")
    set(WITH_OGG                  ON CACHE BOOL "")
    set(BUILD_SHARED_LIBS         OFF CACHE BOOL "")

    add_definitions(-DSR_AUDIO_USE_FLAC)
    add_subdirectory(libs/flac)

    if (UNIX)
        target_compile_options(FLAC PRIVATE -fPIC)
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
endif()

target_link_libraries(Audio PUBLIC modplug)
target_include_directories(Audio PUBLIC libs/libmodplug/src)

if (SR_AUDIO_USE_VORBIS)
    target_link_libraries(Audio PUBLIC vorbis vorbisfile ogg)
    target_include_directories(Audio PUBLIC libs/vorbis/include)
endif()

if (SR_AUDIO_USE_FLAC)
    target_link_libraries(Audio PUBLIC FLAC)
    target_include_directories(Audio PUBLIC libs/flac/include)
endif()

target_include_directories(Audio PUBLIC inc)
target_include_directories(Audio PUBLIC libs)

if (SR_USE_PCH)
    target_compile_definitions(Audio PUBLIC SR_USE_PCH)
    target_precompile_headers(Audio PUBLIC ${SR_COMMON_PCH_HEADER_PATH})
endif()

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
target_include_directories(Audio PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})

set_target_properties(Audio PROPERTIES
    BUILD_RPATH "\$ORIGIN"
    INSTALL_RPATH "\$ORIGIN"
)
