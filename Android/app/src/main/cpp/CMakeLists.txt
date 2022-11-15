cmake_minimum_required(VERSION 3.16)
project("SpaRcleEngineAndroid")

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -Wall -Werror")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Engine/Core ${CMAKE_CURRENT_BINARY_DIR}/Engine/Core)

add_library(sparcle SHARED
    main.cpp android_native_app_glue.c
)

find_library(log-lib log)

target_link_libraries(sparcle
    ${log-lib}
    android
    EGL
    Core
    GLESv1_CM
)

target_include_directories(sparcle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Engine/Core/inc)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
