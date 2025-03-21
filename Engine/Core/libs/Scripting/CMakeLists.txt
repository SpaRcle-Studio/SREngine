cmake_minimum_required(VERSION 3.16)
project(Scripting)

set(CMAKE_CXX_STANDARD 20)

#include(ExternalProject)

#set(SR_MONO_INSTALL_DIR "${CMAKE_BINARY_DIR}/OpenMono")
#set(SR_MONO_MSI_PATH "${CMAKE_BINARY_DIR}/mono-installer.exe")
#set(SR_MONO_INSTALL_URL "https://download.mono-project.com/archive/6.12.0/windows-installer/mono-6.12.0.206-x64-0.msi")
#set(SR_MONO_INSTALL_URL "https://mono-developer-documentation.readthedocs.io/en/latest/downloads/windows.html")
#set(SR_MONO_INSTALL_URL "https://objects.githubusercontent.com/github-production-release-asset-2e65be/45037350/32b40f18-6bac-11e7-8b1d-b7f471104e52?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=releaseassetproduction%2F20250314%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20250314T160553Z&X-Amz-Expires=300&X-Amz-Signature=730dbe8e25530d3308baa7776fc3d9ceb1a8ce72ffc62862cd4e00eb49d34e34&X-Amz-SignedHeaders=host&response-content-disposition=attachment%3B%20filename%3DOpenMonoSetup-v1.7.3.exe&response-content-type=application%2Foctet-stream")

#file(MAKE_DIRECTORY ${SR_MONO_INSTALL_DIR})
#
#message(STATUS "Mono install dir: ${SR_MONO_INSTALL_DIR}")
#message(STATUS "Mono install url: ${SR_MONO_INSTALL_URL}")

# Скачиваем вручную
#file(DOWNLOAD
#    ${SR_MONO_INSTALL_URL}
#    ${SR_MONO_MSI_PATH}
#    SHOW_PROGRESS
#    STATUS download_status
#)
#
#list(GET download_status 0 download_result)
#if(NOT download_result EQUAL 0)
#    message(FATAL_ERROR "Failed to download Mono. Status: ${download_status}")
#endif()

#message(STATUS "Mono downloaded successfully to: ${SR_MONO_MSI_PATH}")

# Устанавливаем Mono
#ExternalProject_Add(mono_install
#    DOWNLOAD_COMMAND ""
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND ""
#    INSTALL_COMMAND msiexec /i "${SR_MONO_MSI_PATH}" /qn /norestart INSTALLDIR="${SR_MONO_INSTALL_DIR}"
#)

#set(Mono_ROOT ${SR_MONO_INSTALL_DIR})
#set(MONO_EXECUTABLE "${SR_MONO_INSTALL_DIR}/bin/mono.exe")
#set(XBUILD_EXECUTABLE "${SR_MONO_INSTALL_DIR}/bin/xbuild.exe")

#include(cmake/InstallMono.cmake)

#set(MONO_ONLY_LIBRARIES_REQUIRED TRUE)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
#find_package(Mono REQUIRED)

#message(STATUS "Mono_ROOT: ${Mono_ROOT}")
#message(STATUS "Mono library: ${MONO_LIBRARIES}")
#message(STATUS "Mono include dir: ${MONO_INCLUDE_DIRS}")

# mono build
#set(SR_MONO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/mono)
#set(SR_MONO_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/mono_build)
#set(SR_MONO_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/mono_install)
#
#file(MAKE_DIRECTORY ${SR_MONO_BUILD_DIR})
#file(MAKE_DIRECTORY ${SR_MONO_INSTALL_DIR})
#
#include(ProcessorCount)
#ProcessorCount(N)
#
#add_custom_target(mono_build
#    COMMAND bash -c "${SR_MONO_SRC_DIR}/autogen.sh --prefix=${SR_MONO_INSTALL_DIR}"
#    WORKING_DIRECTORY ${SR_MONO_BUILD_DIR}
#    COMMENT "Building Mono..."
#    VERBATIM
#)
# mono build

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

set(SR_MONO_DOTNET "${SR_VENV_DIR}/DotnetPrebuild")

if (SR_ENGINE_MONO_SUPPORT)
    if (SR_ENGINE_USE_MONO_PREBUILD)
        if (SR_ENGINE_USE_MONO_DOTNET)
            set(__SR_MONO_DOTNET_LIB_EXT ".lib")
            set(__SR_MONO_DOTNET_LIB_PREFIX "")

            if (UNIX)
                set(__SR_MONO_DOTNET_LIB_PREFIX "lib")
                set(__SR_MONO_DOTNET_LIB_EXT ".a")
            endif()

            if (SR_ENGINE_BUILD_TYPE STREQUAL "Debug")
                set(__SR_MONO_DOTNET_LIB_CONFIG "debug")
            else()
                set(__SR_MONO_DOTNET_LIB_CONFIG "release")
            endif()

            if (ANDROID_NDK)
                if(ANDROID_ABI STREQUAL "arm64-v8a")
                    set(__SR_MONO_DOTNET_LIB_ARCH "android-arm64")
                elseif(ANDROID_ABI STREQUAL "x86_64")
                    set(__SR_MONO_DOTNET_LIB_ARCH "android-x64")
                else()
                    message(FATAL_ERROR "Unsupported Android ABI: ${ANDROID_ABI}. Supported ABIs are: arm64-v8a, x86_64.")
                endif()
            elseif (UNIX)
                set(__SR_MONO_DOTNET_LIB_ARCH "linux-x64")
            elseif (WIN32)
                set(__SR_MONO_DOTNET_LIB_ARCH "windows-x64")
            else()
                message(FATAL_ERROR "Unsupported platform for Mono .NET libraries.")
            endif()

            set(MONO_INCLUDE_DIRS "${SR_MONO_DOTNET}/include/mono-2.0")

            list(APPEND MONO_LIBRARIES_LIST_RAW "monosgen-2.0")
            list(APPEND MONO_LIBRARIES_LIST_RAW "mono-component-debugger-static")
            list(APPEND MONO_LIBRARIES_LIST_RAW "mono-component-diagnostics_tracing-static")
            list(APPEND MONO_LIBRARIES_LIST_RAW "mono-component-hot_reload-static")
            list(APPEND MONO_LIBRARIES_LIST_RAW "mono-component-marshal-ilgen-static")

            #if (ANDROID_NDK)
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "System.Security.Cryptography.Native.Android")
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "System.Globalization.Native")
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "System.IO.Compression.Native")
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "System.IO.Ports.Native")
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "System.Native")
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "brotlienc")
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "brotlidec")
            #    list(APPEND MONO_LIBRARIES_LIST_RAW "brotlicommon")
            #    #list(APPEND MONO_LIBRARIES_LIST_RAW "libz")
            #endif()

            foreach (lib IN LISTS MONO_LIBRARIES_LIST_RAW)
                list(APPEND MONO_LIBRARIES "${SR_MONO_DOTNET}/lib/${__SR_MONO_DOTNET_LIB_CONFIG}-${__SR_MONO_DOTNET_LIB_ARCH}/${__SR_MONO_DOTNET_LIB_PREFIX}${lib}${__SR_MONO_DOTNET_LIB_EXT}")
            endforeach()

            message(STATUS "SREngine mono libraries: ${MONO_LIBRARIES}")

            #list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmonosgen-2.0.a")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-profiler-log.a")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-debugger-static.a")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-diagnostics_tracing-static.a")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-marshal-ilgen-static.a")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-hot_reload-static.a")

            #list(APPEND MONO_LIBRARIES "${__SR_MONO_DOTNET_LIB}/mono-component-debugger-static.lib")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_DOTNET_LIB}/mono-component-diagnostics_tracing-static.lib")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_DOTNET_LIB}/mono-component-hot_reload-static.lib")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_DOTNET_LIB}/mono-component-marshal-ilgen-static.lib")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_DOTNET_LIB}/mono-profiler-aot.lib")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_DOTNET_LIB}/monosgen-2.0.lib")
            #list(APPEND MONO_LIBRARIES "${__SR_MONO_DOTNET_LIB}/System.Globalization.Native.Aot.lib")
        else()
            if (SR_ENGINE_USE_MONO_DOTNET)
                message(FATAL_ERROR "Dotnet build not supported yet!")
            endif()

            if (ANDROID_NDK)
                if(ANDROID_ABI STREQUAL "arm64-v8a")
                    message(STATUS "Building SREngine with Mono for ARM64 abi")
                    set(__SR_MONO_ANDROID "${SR_VENV_DIR}/MonoAndroid/android-arm64/native")
                elseif(ANDROID_ABI STREQUAL "x86_64")
                    message(STATUS "Building SREngine with Mono for x86_64 abi")
                    set(__SR_MONO_ANDROID "${SR_VENV_DIR}/MonoAndroid/android-x64/native")
                else()
                    message(FATAL_ERROR "Unsupported Android ABI: ${ANDROID_ABI}. Supported ABIs are: arm64-v8a, x86_64.")
                endif()

                set(MONO_INCLUDE_DIRS "${__SR_MONO_ANDROID}/include/mono-2.0")

                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmonosgen-2.0.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-debugger-static.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-diagnostics_tracing-static.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-marshal-ilgen-static.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libmono-component-hot_reload-static.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libSystem.Globalization.Native.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libSystem.IO.Compression.Native.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libSystem.Native.a")
                list(APPEND MONO_LIBRARIES "${__SR_MONO_ANDROID}/libSystem.Security.Cryptography.Native.Android.a")
            elseif (UNIX)
                # Find Mono installation
                find_package(PkgConfig REQUIRED)
                pkg_check_modules(MONO REQUIRED mono-2)
            else()
                include(cmake/CloneMonoPrebuild.cmake)
            endif()
        endif()
    else()
        if (WIN32)
            include(cmake/CloneMonoSources.cmake)
            include(cmake/InstallMonoBuildTool.cmake)
            include(cmake/InstallCygwin.cmake)
            include(cmake/BuildMono.cmake)
        else()
            message(FATAL_ERROR "Mono build is not supported on this platform.")
        endif()
    endif()
endif()

if (EVO_SCRIPT_STATIC_LIBRARY)
    target_link_libraries(Scripting EvoScriptCore)
else()
    target_link_libraries(Scripting EvoScriptCore::lib)
endif()

if (SR_ENGINE_MONO_SUPPORT)
    if (WIN32)
        # for mono correct link
        target_link_libraries(Scripting version bcrypt)
    endif()

    target_include_directories(Scripting PUBLIC ${MONO_INCLUDE_DIRS})
    target_link_libraries(Scripting ${MONO_LIBRARIES})
endif()

target_include_directories(Scripting PUBLIC inc)
target_include_directories(Scripting PUBLIC libs/EvoScript/Core/inc)
target_include_directories(Scripting PUBLIC libs)

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
target_include_directories(Scripting PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})