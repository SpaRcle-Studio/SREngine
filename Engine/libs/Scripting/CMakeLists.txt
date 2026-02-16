cmake_minimum_required(VERSION 3.16)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT MSVC AND NOT ANDROID_NDK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
endif()

project(Scripting)

SR_COMMON_GENERATE_BUILD_SOURCES(${PROJECT_SOURCE_DIR})
SR_COMMON_GET_SOURCES(Scripting)

set(CMAKE_CXX_STANDARD 20)

option(SR_SCRIPTING_DLL_EXPORTS "" ON)

if (SR_SCRIPTING_STATIC_LIBRARY)
    add_library(Scripting STATIC ${Scripting_SOURCES})
else()
    add_library(Scripting SHARED ${Scripting_SOURCES})
    add_library(Scripting::lib ALIAS Scripting)

    if (UNIX)
        target_compile_options(Scripting PRIVATE -fPIC)
        
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_link_libraries(Scripting atomic)
        endif()
    endif()

    target_link_libraries(Scripting Utils)

    SR_COPY_SHARED_MODULE_TO_EXECUTABLE_FOLDER(Scripting)
    SR_COPY_STATIC_LIBRARY_TO_LIBRARY_FOLDER(Scripting)
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
target_include_directories(Scripting PUBLIC ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Engine/libs/Utils/libs/tree-sitter/lib/include)
target_include_directories(Scripting PUBLIC libs)

if (SR_USE_PCH)
    target_compile_definitions(Scripting PUBLIC SR_USE_PCH)
    target_precompile_headers(Scripting PUBLIC ${SR_COMMON_PCH_HEADER_PATH})
endif()

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
target_include_directories(Scripting PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})

set_target_properties(Scripting PROPERTIES
    BUILD_RPATH "\$ORIGIN"
    INSTALL_RPATH "\$ORIGIN"
)
