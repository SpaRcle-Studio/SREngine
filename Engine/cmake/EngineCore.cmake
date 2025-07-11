if (ANDROID_NDK)
    add_compile_options(-femulated-tls)
    add_link_options(-femulated-tls)
endif()

set(SR_UTILS_DLL_EXPORTS ON CACHE INTERNAL "" FORCE)

if (SR_TRACY_ENABLE)
    add_definitions(
        -DSR_TRACY_ENABLE
        -DTRACY_ON_DEMAND
        -DTRACY_ENABLE
    )
endif()

option(SR_ENGINE_DLL_EXPORTS "" ON)

set(CORE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

SET(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
SET(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)

if (ANDROID_NDK)
    if (${ANDROID_ABI} STREQUAL "x86_64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mlzcnt -mpopcnt")
    endif()

    add_definitions(
        -DGLM_LANG_STL11_FORCED
        -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES
    )
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

if (MINGW)
else()
    if (ANDROID_NDK)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcomment -Wno-comment -Woverloaded-virtual -Wno-everything -Wmissing-braces -Wunused-private-field -Wno-unused-private-field")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcomment -Wno-comment -Woverloaded-virtual -Wno-everything -Wmissing-braces -Wunused-private-field -Wno-unused-private-field")
    else()
        if (MSVC)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /utf-8")
        else ()
            add_compile_options(-fexec-charset=UTF-8)
        endif ()
    endif()
endif()

if (NOT SR_ENGINE_FLATPAK_BUILD AND NOT ANDROID_NDK)
    include(libs/Utils/cmake/ResourceEmbedder.cmake)

    AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/Threads.yml")
    AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/Features.xml")

    if (WIN32)
        AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Utilities/git2.exe")
        AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Utilities/vswhere.exe")
    elseif (UNIX)
        AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Utilities/git2")
    endif()

    EmbedResources("${CMAKE_CURRENT_BINARY_DIR}/libs/Utils/include/Utils" "Resources" ${EMBED_RESOURCES_LIST})

    set(SR_COMMON_EMBED_RESOURCES ON)
endif()

set(SR_COMMON_GIT_METADATA ON)

add_compile_definitions(SR_COMMON_GIT_METADATA)

message(STATUS "SpaRcle Engine: CONFIGURING Utils")
add_subdirectory(libs/Utils)

if (NOT SR_EMSCRIPTEN AND NOT SR_COMMON_USE_CLANG_EMULATION)
    set(SR_PHYSICS_USE_PHYSX ON)
else()
    set(SR_PHYSICS_USE_PHYSX OFF)
    message(STATUS "SpaRcle Engine: PhysX is disabled because Clang emulation is used or Emscripten build")
endif()

message(STATUS "SpaRcle Engine: CONFIGURING Audio")
add_subdirectory(libs/Audio)
message(STATUS "SpaRcle Engine: CONFIGURING Physics")
add_subdirectory(libs/Physics)
message(STATUS "SpaRcle Engine: CONFIGURING Graphics")
add_subdirectory(libs/Graphics)
message(STATUS "SpaRcle Engine: CONFIGURING Scripting")
add_subdirectory(libs/Scripting)

set(SR_ENGINE_CORE_SOURCES
    ${CORE_ROOT_DIR}/cxx/Core.cxx
    ${CORE_ROOT_DIR}/cxx/GUI.cxx
    ${CORE_ROOT_DIR}/cxx/Codegen.cxx
    ${CORE_ROOT_DIR}/cxx/States.cxx
    ${CORE_ROOT_DIR}/src/Engine/EntryPoint.cpp
)

if (SR_ENGINE_STATIC_LIBRARY)
    add_library(Engine STATIC ${SR_ENGINE_CORE_SOURCES})
else()
    add_library(Engine SHARED ${SR_ENGINE_CORE_SOURCES})
    add_library(Engine::lib ALIAS Engine)

    if (UNIX)
        target_compile_options(Graphics PRIVATE -fPIC)
    endif()

    SR_COPY_SHARED_MODULE_TO_EXECUTABLE_FOLDER(Engine)
    SR_COPY_STATIC_LIBRARY_TO_LIBRARY_FOLDER(Engine)
endif()

if (SR_ENGINE_DLL_EXPORTS)
    message("Engine will be using DLL exports")
    target_compile_definitions(Engine PUBLIC SR_ENGINE_DLL_EXPORTS)
endif()

list(APPEND SR_CORE_LINK_LIBRARIES Utils)
list(APPEND SR_CORE_LINK_LIBRARIES Physics)
list(APPEND SR_CORE_LINK_LIBRARIES Graphics)
list(APPEND SR_CORE_LINK_LIBRARIES Audio)
list(APPEND SR_CORE_LINK_LIBRARIES Scripting)

target_link_libraries(Engine ${SR_CORE_LINK_LIBRARIES})

target_include_directories(Engine PUBLIC ${CORE_ROOT_DIR}/inc)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(Engine PUBLIC ${SR_CMAKE_ROOT_BUILD_DIRECTORY}/Codegen)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Utils/include)
target_include_directories(Engine PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Utils/libs/assimp/include)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs)
target_include_directories(Engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs/assimp/include)