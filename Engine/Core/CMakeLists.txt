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
        if (MSVC)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /utf-8")
        else ()
            add_compile_options(-fexec-charset=UTF-8)
        endif ()
    endif()
endif()

include(libs/Utils/cmake/ResourceEmbedder.cmake)
#include(libs/Utils/cmake/Codegen.cmake)

#SRUtilsCodegen("${CMAKE_CURRENT_SOURCE_DIR}/../../" "${CMAKE_CURRENT_SOURCE_DIR}/config/codegen.xml" "${CMAKE_CURRENT_BINARY_DIR}/Codegen/")

AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/Features.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/Layers.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/TagManagerSettings.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/EvoScript.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/SRLMTypes.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/World.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/Physics.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/MainRenderTechnique.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Configs/Themes/Dark.xml")


AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/PhysicsMaterials/DefaultMaterial.physmat")

AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Textures/default_improved.png")

AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Shaders/SSAO/ssao_geometry.srsl")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Shaders/ui.srsl")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Shaders/wireframe.srsl")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Shaders/line.srsl")


AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Materials/default.mat")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Materials/UI/ui.mat")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Materials/Debug/wireframe.mat")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Materials/Debug/line.mat")


AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Fonts/tahoma.ttf")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Engine/Fonts/fa-solid-900.ttf")


AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Editor/Configs/ImGuiEditor.config")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Editor/Configs/EditorWidgets.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Editor/Configs/OverlayRenderTechnique.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Editor/Configs/EditorSettings.xml")
AddEmbedResource("${CMAKE_SOURCE_DIR}/Resources/Editor/Configs/EditorCascadedShadowMapRenderTechnique.xml")

EmbedResources("${CMAKE_CURRENT_BINARY_DIR}/libs/Utils/include/Utils" "SREngine/Resources" ${EMBED_RESOURCES_LIST})

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

add_library(Core STATIC ${CORE_ROOT_DIR}/cxx/Core.cxx ${CORE_ROOT_DIR}/cxx/GUI.cxx ${CORE_ROOT_DIR}/cxx/Codegen.cxx)

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

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Utils/include)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Utils/libs/assimp/include)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Utils/libs/FQHSA/header)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils/libs/assimp/include)