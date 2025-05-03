cmake_minimum_required(VERSION 3.16)
project(Scripting)

set(CMAKE_CXX_STANDARD 20)

option(SR_SCRIPTING_DLL_EXPORTS "" ON)

if (SR_SCRIPTING_STATIC_LIBRARY)
    add_library(Scripting STATIC Scripting.cxx)
else()
    add_library(Scripting SHARED Scripting.cxx)
    add_library(Scripting::lib ALIAS Scripting)

    if (UNIX)
        target_compile_options(Scripting PRIVATE -fPIC)
    endif()

    target_link_libraries(Scripting PUBLIC Utils)

    SR_COPY_SHARED_MODULE_TO_EXECUTABLE_FOLDER(Scripting)
endif()

if (SR_SCRIPTING_DLL_EXPORTS)
    message("Scripting will be using DLL exports")
    target_compile_definitions(Scripting PUBLIC SR_SCRIPTING_DLL_EXPORTS)
endif()

if (SR_ENGINE_MONO_SUPPORT)
    if (SR_ENGINE_USE_MONO_PREBUILD)
        if (UNIX AND NOT ANDROID_NDK)
            # Find Mono installation
            find_package(PkgConfig REQUIRED)
            pkg_check_modules(MONO REQUIRED mono-2)
        else()
            include(cmake/CloneMonoPrebuild.cmake)
        endif()
    else()
        if (WIN32 OR ANDROID_NDK)
            include(cmake/CloneMonoSources.cmake)
            include(cmake/InstallMonoBuildTool.cmake)
            include(cmake/InstallCygwin.cmake)
            include(cmake/BuildMono.cmake)
        endif()
    endif()

    if (UNIX AND NOT ANDROID_NDK)
        target_include_directories(Scripting PUBLIC ${MONO_INCLUDE_DIRS})
        target_link_libraries(Scripting ${MONO_LIBRARIES})
    else()
        target_link_libraries(Scripting ${Mono_LIBRARY})

        if (WIN32 OR ANDROID_NDK)
            # for mono correct link
            target_link_libraries(Scripting version bcrypt)
        endif()

        target_include_directories(Scripting PUBLIC ${Mono_INCLUDE_DIR})
    endif()
endif()

target_include_directories(Scripting PUBLIC inc)
target_include_directories(Scripting PUBLIC libs/EvoScript/Core/inc)
target_include_directories(Scripting PUBLIC ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Engine/Core/libs/Utils/libs/tree-sitter/lib/include)
target_include_directories(Scripting PUBLIC libs)

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
target_include_directories(Scripting PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})