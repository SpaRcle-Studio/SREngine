cmake_minimum_required(VERSION 3.16)
project(Audio)

set(CMAKE_CXX_STANDARD 20)

add_definitions(
    -DMODPLUG_STATIC
    -DFLAC__NO_DLL
)

add_subdirectory(libs/OpenAL)
add_subdirectory(libs/libmodplug)

if (SR_AUDIO_STATIC_LIBRARY)
    add_library(Audio STATIC Audio.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Audio SHARED Audio.cxx)
    add_library(Audio::lib ALIAS Audio)
endif()

target_link_libraries(Audio modplug)

target_include_directories(Audio PUBLIC inc)
target_include_directories(Audio PUBLIC libs)
target_include_directories(Audio PUBLIC libs/OpenAL/include)
target_include_directories(Audio PUBLIC libs/libmodplug/src)
target_include_directories(Audio PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)

