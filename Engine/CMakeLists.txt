cmake_minimum_required(VERSION 3.16)
project(SpaRcleEngine)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fconcepts-ts")

add_subdirectory(Core)

if(EXISTS "${CMAKE_BINARY_DIR}/bin/glew32d.dll")
    file(COPY ${CMAKE_BINARY_DIR}/bin/glew32d.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
endif()

if(EXISTS "${CMAKE_BINARY_DIR}/bin/glew32.dll")
    file(COPY ${CMAKE_BINARY_DIR}/bin/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
endif()

add_executable(Engine main.cpp)

target_link_libraries(Engine Core)

