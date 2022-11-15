cmake_minimum_required(VERSION 3.16)
project(Core)

message("SpaRcle Engine compiler: ${CMAKE_C_COMPILER}")

set(CORE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

SET(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
SET(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)

set(SR_UTILS_STATIC_LIBRARY ON)
set(SR_AUDIO_STATIC_LIBRARY ON)
set(SR_PHYSICS_STATIC_LIBRARY ON)
set(SR_GRAPHICS_STATIC_LIBRARY ON)
set(SR_SCRIPTING_STATIC_LIBRARY ON)

set(EVO_VULKAN_STATIC_LIBRARY ON)
set(EVO_SCRIPT_STATIC_LIBRARY ON)

if (ANDROID_NDK)
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
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wc++17-extensions -Wimplicit-fallthrough -Wc++17-attribute-extensions -Wunused-variable -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wdeprecated-volatile -Wunused-function")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wc++17-extensions -Wimplicit-fallthrough -Wc++17-attribute-extensions -Wunused-variable -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wdeprecated-volatile -Wunused-function")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wreorder-ctor -Wno-reorder -Wmissing-field-initializers -Wunused-value")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wreorder-ctor -Wno-reorder -Wmissing-field-initializers -Wunused-value")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcomment -Wno-comment -Woverloaded-virtual -Wno-everything -Wmissing-braces -Wunused-private-field -Wno-unused-private-field")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcomment -Wno-comment -Woverloaded-virtual -Wno-everything -Wmissing-braces -Wunused-private-field -Wno-unused-private-field")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /utf-8")
    endif()
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
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)