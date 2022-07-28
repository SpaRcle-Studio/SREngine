cmake_minimum_required(VERSION 3.16)
project(SpaRcleEngine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Core)

add_executable(Engine main.cpp)

add_custom_command(TARGET Engine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        -DTARGET_NAME=Engine
        -DTARGET_PATH=${CMAKE_BINARY_DIR}
        -P ${CMAKE_SOURCE_DIR}/Engine/post_build.cmake
        COMMENT "Running SpaRcle engine post-build script..."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(Engine Core)

