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

message(STATUS "CONFIGURING Utils -----------------")
add_subdirectory(libs/Utils)
message(STATUS "CONFIGURING Audio -----------------")
add_subdirectory(libs/Audio)
message(STATUS "CONFIGURING Physics -----------------")
add_subdirectory(libs/Physics)
message(STATUS "CONFIGURING Graphics -----------------")
add_subdirectory(libs/Graphics)
message(STATUS "CONFIGURING Scripting -----------------")
add_subdirectory(libs/Scripting)

add_library(Engine STATIC
    ${CORE_ROOT_DIR}/cxx/Core.cxx
    ${CORE_ROOT_DIR}/cxx/GUI.cxx
    ${CORE_ROOT_DIR}/cxx/Codegen.cxx
    ${CORE_ROOT_DIR}/cxx/States.cxx
)

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
target_include_directories(Engine PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Utils/libs/FQHSA/header)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs)
target_include_directories(Engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs/assimp/include)