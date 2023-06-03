cmake_minimum_required(VERSION 3.16)
project(Scripting)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/EvoScript/Core)

if (SR_SCRIPTING_STATIC_LIBRARY)
    add_library(Scripting STATIC Scripting.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Scripting SHARED Scripting.cxx)
    add_library(Scripting::lib ALIAS Scripting)
endif()

if (EVO_SCRIPT_STATIC_LIBRARY)
    target_link_libraries(Scripting EvoScriptCore)
else()
    target_link_libraries(Scripting EvoScript::lib)
endif()

target_include_directories(Scripting PUBLIC inc)
target_include_directories(Scripting PUBLIC libs/EvoScript/Core/inc)
target_include_directories(Scripting PUBLIC libs)
target_include_directories(Scripting PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Scripting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)
target_include_directories(Scripting PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include/tracy/tracy)