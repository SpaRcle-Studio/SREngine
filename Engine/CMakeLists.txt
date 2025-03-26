cmake_minimum_required(VERSION 3.16)
project(SpaRcleEngine)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/TargetArchitecture.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/InstallPython.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Codegen.cmake)

SRCodegen()

target_architecture(CURRENT_TARGET_ARCHITECTURE)
message(STATUS "SpaRcle Engine: current build target architecture: ${CURRENT_TARGET_ARCHITECTURE}")
message(STATUS "SpaRcle Engine: current build type: ${CMAKE_BUILD_TYPE}")

get_property(SR_ENGINE_VERSION GLOBAL PROPERTY SR_ENGINE_VERSION_PROPERTY)
get_property(SR_ENGINE_MAJOR_VERSION GLOBAL PROPERTY SR_ENGINE_MAJOR_VERSION_PROPERTY)
get_property(SR_ENGINE_MINOR_VERSION GLOBAL PROPERTY SR_ENGINE_MINOR_VERSION_PROPERTY)
get_property(SR_ENGINE_PATCH_VERSION GLOBAL PROPERTY SR_ENGINE_PATCH_VERSION_PROPERTY)

message(STATUS "SpaRcle Engine: current version is ${SR_ENGINE_VERSION}")
message(STATUS "SpaRcle Engine: C compiler is '${CMAKE_C_COMPILER}'")
message(STATUS "SpaRcle Engine: C++ compiler is '${CMAKE_CXX_COMPILER}'")

option(SR_ENGINE_FLATPAK_BUILD "" OFF)

option(SR_ENGINE_USE_MONO_PREBUILD "" ON)

if (WIN32 OR (UNIX AND NOT ANDROID_NDK))
    option(SR_ENGINE_MONO_SUPPORT "" ON)
    add_compile_definitions(SR_ENGINE_MONO_SUPPORT)
else()
    option(SR_ENGINE_MONO_SUPPORT "" OFF)
endif()

if (SR_ENGINE_FLATPAK_BUILD)
    add_compile_definitions(SR_ENGINE_FLATPAK_BUILD)
endif()

if (ANDROID_NDK)
    add_compile_options(-femulated-tls)
    add_link_options(-femulated-tls)
endif()

# TODO!
#add_compile_definitions(_CONTAINER_DEBUG_LEVEL=0)
#add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)

set(SR_UTILS_ASSIMP ON CACHE INTERNAL "" FORCE)
set(SR_UTILS_DLL_EXPORTS ON CACHE INTERNAL "" FORCE)

if (SR_TRACY_ENABLE)
    add_definitions(
        -DSR_TRACY_ENABLE
        -DTRACY_ON_DEMAND
        -DTRACY_ENABLE
    )
endif()

add_subdirectory(Core)
add_subdirectory(Scripts)

define_property(GLOBAL PROPERTY SR_EXECUTABLE_ARGS)
set_property(GLOBAL PROPERTY SR_EXECUTABLE_ARGS "")

if (ANDROID_NDK)
    set(SR_EXECUTABLE_NAME "sparcle")

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

    add_library(${SR_EXECUTABLE_NAME} SHARED "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Android/app/src/main/cpp/main.cpp")

    set_target_properties(sparcle PROPERTIES DEBUG_POSTFIX "")

    find_library(log-lib log)

    target_link_libraries(${SR_EXECUTABLE_NAME}
        ${log-lib}
        android
        EGL
        GLESv1_CM
    )
else()
    set(SR_EXECUTABLE_NAME "SREngine")

    set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "main.cpp")

    if (WIN32)
        #add_custom_command(
        #    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resource.res
        #    COMMAND windres ${CMAKE_CURRENT_SOURCE_DIR}/resource.rc -O coff -o ${CMAKE_CURRENT_BINARY_DIR}/resource.res
        #    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resource.rc
        #)
        #set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "${CMAKE_CURRENT_BINARY_DIR}/resource.res")
        #set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "${CMAKE_CURRENT_SOURCE_DIR}/resource.rc")
    endif()

    if (NOT CMAKE_GENERATOR MATCHES "Visual Studio")
        set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")
    endif()

    get_property(SR_EXECUTABLE_ARGS_CONTENT GLOBAL PROPERTY SR_EXECUTABLE_ARGS)
    message(STATUS "SpaRcle Engine: adding executable arguments: ${SR_EXECUTABLE_ARGS_CONTENT}")
    add_executable(${SR_EXECUTABLE_NAME} ${SR_EXECUTABLE_ARGS_CONTENT})

    #target_sources(${SR_EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/resource.rc")
endif()

add_custom_command(TARGET ${SR_EXECUTABLE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -DTARGET_NAME=Engine
    -DTARGET_PATH=${CMAKE_BINARY_DIR}
    -P ${CMAKE_SOURCE_DIR}/Engine/cmake/PostBuild.cmake
    COMMENT "Running SpaRcle engine post-build script..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(${SR_EXECUTABLE_NAME} Core Scripts)
target_include_directories(${SR_EXECUTABLE_NAME} PRIVATE ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Resources/SpaRcleAPI)

if (NOT ANDROID_NDK)
    # TODO: implement an easy way to set if a build is 'stable' or 'latest'
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(executableType "stable")
    else()
        set(executableType "latest")
    endif()

    if (SR_ENGINE_FLATPAK_BUILD)
        install(TARGETS ${SR_EXECUTABLE_NAME} DESTINATION /app/bin)
        install(TARGETS ${SR_EXECUTABLE_NAME} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    endif()

    if (SR_ENGINE_EXTENDED_NAME)
        if (UNIX AND NOT APPLE)
            set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${SR_EXECUTABLE_NAME}_v${SR_ENGINE_VERSION}-${executableType}_linux.${CURRENT_TARGET_ARCHITECTURE}")
        elseif (WIN32)
            set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${SR_EXECUTABLE_NAME}_v${SR_ENGINE_VERSION}-${executableType}_windows.${CURRENT_TARGET_ARCHITECTURE}")
        endif()
    else()
        set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "srengine")
    endif()
endif()