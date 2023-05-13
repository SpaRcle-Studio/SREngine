cmake_minimum_required(VERSION 3.16)
project(Audio)

set(CMAKE_CXX_STANDARD 20)

add_definitions(
    -DMODPLUG_STATIC
    -DFLAC__NO_DLL
    -DAL_LIBTYPE_STATIC
)

set(LIBTYPE STATIC)

set(ALSOFT_INSTALL_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(ALSOFT_INSTALL_UTILS OFF CACHE INTERNAL "" FORCE)
set(ALSOFT_UTILS OFF CACHE INTERNAL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE INTERNAL "" FORCE)

add_subdirectory(libs/OpenAL)
add_subdirectory(libs/libmodplug)

if(MSVC)
    target_compile_options(modplug PRIVATE "/wd5033;")
endif()

if (SR_AUDIO_STATIC_LIBRARY)
    add_library(Audio STATIC Audio.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Audio SHARED Audio.cxx)
    add_library(Audio::lib ALIAS Audio)
endif()

#if (ANDROID_NDK)
#    target_link_libraries(Audio modplug OpenAL)
#else()
#    target_link_libraries(Audio modplug)
#endif()

target_link_libraries(Audio modplug OpenAL)

target_include_directories(Audio PUBLIC inc)
target_include_directories(Audio PUBLIC libs)
target_include_directories(Audio PUBLIC libs/OpenAL/include)
target_include_directories(Audio PUBLIC libs/libmodplug/src)
target_include_directories(Audio PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)
target_include_directories(Audio PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include/tracy/tracy)
