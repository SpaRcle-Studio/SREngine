cmake_minimum_required(VERSION 3.16) #Следует перейти на 3.21 для лучшей работы с Android NDK
project(Core)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "SpaRcle Engine compiler: ${CMAKE_C_COMPILER}")

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
		#TODO: Закомментировано для простоты сборки, чтобы не разбираться с ошибками из-за неиспользованных переменных (НЕ ПИШИТЕ ПЕРЕМЕННЫЕ, НЕ ИСПОЛЬЗУЯ ИХ)
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wc++17-extensions -Wimplicit-fallthrough -Wc++17-attribute-extensions -Wunused-variable -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wdeprecated-volatile -Wunused-function")
        #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wc++17-extensions -Wimplicit-fallthrough -Wc++17-attribute-extensions -Wunused-variable -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wdeprecated-volatile -Wunused-function")

        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wreorder-ctor -Wno-reorder -Wmissing-field-initializers -Wunused-value")
        #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wreorder-ctor -Wno-reorder -Wmissing-field-initializers -Wunused-value")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcomment -Wno-comment -Woverloaded-virtual -Wno-everything -Wmissing-braces -Wunused-private-field -Wno-unused-private-field")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcomment -Wno-comment -Woverloaded-virtual -Wno-everything -Wmissing-braces -Wunused-private-field -Wno-unused-private-field")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /utf-8")
    endif()
endif()

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

add_library(Core STATIC ${CORE_ROOT_DIR}/Core.cxx)

if (SR_UTILS_STATIC_LIBRARY)
    list(APPEND SR_CORE_LINK_LIBRARIES Utils)
else()
    list(APPEND SR_CORE_LINK_LIBRARIES Utils::lib)
endif()

if (SR_PHYSICS_STATIC_LIBRARY)
    list(APPEND SR_CORE_LINK_LIBRARIES Physics)
else()
    list(APPEND SR_CORE_LINK_LIBRARIES Physics::lib)
endif()

if (SR_GRAPHICS_STATIC_LIBRARY)
    list(APPEND SR_CORE_LINK_LIBRARIES Graphics)
else()
    list(APPEND SR_CORE_LINK_LIBRARIES Graphics::lib)
endif()

if (SR_AUDIO_STATIC_LIBRARY)
    list(APPEND SR_CORE_LINK_LIBRARIES Audio)
else()
    list(APPEND SR_CORE_LINK_LIBRARIES Audio::lib)
endif()

if (SR_SCRIPTING_STATIC_LIBRARY)
    list(APPEND SR_CORE_LINK_LIBRARIES Scripting)
else()
    list(APPEND SR_CORE_LINK_LIBRARIES Scripting::lib)
endif()

target_link_libraries(Core ${SR_CORE_LINK_LIBRARIES})

target_include_directories(Core PUBLIC ${CORE_ROOT_DIR}/inc)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Utils/include)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs/assimp/include)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Utils/libs/assimp/include)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Utils/libs/FQHSA/header)