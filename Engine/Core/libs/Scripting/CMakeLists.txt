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
#message(STATUS "Mono library: ${Mono_LIBRARY}")
#message(STATUS "Mono include dir: ${Mono_INCLUDE_DIR}")

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

#target_include_directories(Scripting PUBLIC ${SR_MONO_INSTALL_DIR}/include/mono-2.0)
#target_link_directories(Scripting PUBLIC ${SR_MONO_INSTALL_DIR}/lib)
#add_dependencies(Scripting mono_build)
#target_link_libraries(Scripting PUBLIC mono)

#add_dependencies(Scripting mono_install)

#include(cmake/InstallMSYS2.cmake)
include(cmake/CloneMonoSources.cmake)
include(cmake/InstallMono.cmake)
include(cmake/InstallCygwin.cmake)
include(cmake/BuildMono.cmake)
add_dependencies(Scripting mono-build)

if (EVO_SCRIPT_STATIC_LIBRARY)
    target_link_libraries(Scripting EvoScriptCore)
else()
    target_link_libraries(Scripting EvoScriptCore::lib)
endif()

target_link_libraries(Scripting ${Mono_LIBRARY})
# for mono correct link
target_link_libraries(Scripting version bcrypt)

target_include_directories(Scripting PUBLIC inc)
target_include_directories(Scripting PUBLIC libs/EvoScript/Core/inc)
target_include_directories(Scripting PUBLIC libs)
target_include_directories(Scripting PUBLIC ${Mono_INCLUDE_DIR})

get_property(SR_UTILS_INCLUDE_DIRECTORIES_CONTENT GLOBAL PROPERTY SR_UTILS_INCLUDE_DIRECTORIES)
target_include_directories(Scripting PUBLIC ${SR_UTILS_INCLUDE_DIRECTORIES_CONTENT})