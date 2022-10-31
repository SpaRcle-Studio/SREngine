cmake_minimum_required(VERSION 3.16)
project(Core)

set(CORE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (MINGW)

else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /utf-8")
endif()

add_subdirectory(libs/Utils)
add_subdirectory(libs/Audio)
add_subdirectory(libs/Physics)
add_subdirectory(libs/Graphics)
add_subdirectory(libs/Scripting)

add_library(Core STATIC ${CORE_ROOT_DIR}/Core.cxx)

if (SR_UTILS_STATIC_LIBRARY)
    target_link_libraries(Core Utils)
else()
    target_link_libraries(Core Utils::lib)
endif()

if (SR_PHYSICS_STATIC_LIBRARY)
    target_link_libraries(Core Physics)
else()
    target_link_libraries(Core Physics::lib)
endif()

if (SR_GRAPHICS_STATIC_LIBRARY)
    target_link_libraries(Core Graphics)
else()
    target_link_libraries(Core Graphics::lib)
endif()

if (SR_AUDIO_STATIC_LIBRARY)
    target_link_libraries(Core Audio)
else()
    target_link_libraries(Core Audio::lib)
endif()

if (SR_SCRIPTING_STATIC_LIBRARY)
    target_link_libraries(Core Scripting)
else()
    target_link_libraries(Core Scripting::lib)
endif()

target_include_directories(Core PUBLIC ${CORE_ROOT_DIR}/inc)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)