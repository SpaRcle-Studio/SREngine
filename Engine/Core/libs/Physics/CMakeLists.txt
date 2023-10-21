cmake_minimum_required(VERSION 3.16)
project(Physics)

set(CMAKE_CXX_STANDARD 20)

add_definitions(
    -DMODPLUG_STATIC
    -DFLAC__NO_DLL
)

# ----------------------------------------------------------------------------------------------------------------------
if (SR_PHYSICS_USE_BOX2D)
    add_compile_definitions(SR_PHYSICS_USE_BOX2D)

    set(BOX2D_BUILD_UNIT_TESTS OFF CACHE INTERNAL "" FORCE)
    set(BOX2D_BUILD_TESTBED OFF CACHE INTERNAL "" FORCE)

    add_subdirectory(libs/box2d)

    list(APPEND SR_PHYSICS_LINK_LIBRARIES box2d)
endif()
# ----------------------------------------------------------------------------------------------------------------------
if (SR_PHYSICS_USE_BULLET3)
    add_compile_definitions(SR_PHYSICS_USE_BULLET3)

    set(BUILD_EXTRAS OFF CACHE INTERNAL "" FORCE)
    set(BUILD_PYBULLET OFF CACHE INTERNAL "" FORCE)
    set(BUILD_UNIT_TESTS OFF CACHE INTERNAL "" FORCE)
    set(BUILD_CLSOCKET OFF CACHE INTERNAL "" FORCE)
    set(BUILD_SERIALIZE_EXTRA OFF CACHE INTERNAL "" FORCE)
    set(BUILD_ENET OFF CACHE INTERNAL "" FORCE)
    set(BUILD_BULLET_ROBOTICS_GUI_EXTRA OFF CACHE INTERNAL "" FORCE)
    set(BUILD_CPU_DEMOS OFF CACHE INTERNAL "" FORCE)
    set(BUILD_OPENGL3_DEMOS OFF CACHE INTERNAL "" FORCE)
    set(BUILD_BULLET2_DEMOS OFF CACHE INTERNAL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)

    add_subdirectory(libs/bullet3)

    list(APPEND SR_PHYSICS_LINK_LIBRARIES Bullet3Common)
    list(APPEND SR_PHYSICS_LINK_LIBRARIES BulletSoftBody)
    list(APPEND SR_PHYSICS_LINK_LIBRARIES BulletInverseDynamicsUtils)
    list(APPEND SR_PHYSICS_LINK_LIBRARIES BulletInverseDynamics)
    list(APPEND SR_PHYSICS_LINK_LIBRARIES BulletDynamics)
    list(APPEND SR_PHYSICS_LINK_LIBRARIES BulletCollision)
    list(APPEND SR_PHYSICS_LINK_LIBRARIES LinearMath)

    if(MSVC)
        target_compile_options(BulletCollision PUBLIC "/wd4828;")
    endif()
endif()
# ----------------------------------------------------------------------------------------------------------------------
if (SR_PHYSICS_USE_PHYSX)
    option(PHYSX_BUILD_TYPE "debug")

    set(PHYSX_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/PhysX/physx)
    set(PHYSX_INCLUDE_DIRS ${PHYSX_ROOT_DIR}/include/ ${PHYSX_ROOT_DIR}/../pxshared/include/)
    set(CMAKEMODULES_PATH ${PHYSX_ROOT_DIR}/../externals/cmakemodules)

    set(PX_BUILDSNIPPETS OFF CACHE BOOL "Generate the snippets")
    set(PX_USE_PLATFORM_MAP_FLAG OFF CACHE BOOL "Use platform MAP flag")
    set(PX_BUILDPUBLICSAMPLES OFF CACHE BOOL "Generate the samples projects")

    set(PX_FLOAT_POINT_PRECISE_MATH OFF CACHE BOOL "Float point precise math")
    set(NV_USE_STATIC_WINCRT OFF CACHE BOOL "Use the statically linked windows CRT")
    set(PXSHARED_PATH ${PHYSX_ROOT_DIR}/../pxshared)
    set(PXSHARED_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
    #set(CMAKEMODULES_VERSION "1.27")
    set(CMAKEMODULES_PATH ${PHYSX_ROOT_DIR}/../externals/cmakemodules)
    set(PX_OUTPUT_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/extern/physx)
    set(PX_OUTPUT_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/extern/physx)

    add_subdirectory(libs/PhysX/physx/source/compiler/cmake)

#[[    if(CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        message("Building physics in debug configuration")
        add_compile_definitions(_DEBUG)
        link_directories("PhysX/bin/linux.clang/debug") # This is the path where PhysX libraries are installed
    else()
        message("Building physics in release configuration with PhysX ${PHYSX_BUILD_TYPE} configuration")
        add_compile_definitions(NDEBUG)
        link_directories("physx/source/compiler\cmake/${PHYSX_BUILD_TYPE}") # This is the path where PhysX libraries are installed
    endif()]]

    #list(APPEND SR_PHYSICS_LINK_LIBRARIES PhysXExtensions_static_64)
    #list(APPEND SR_PHYSICS_LINK_LIBRARIES PhysX_static_64)
    #list(APPEND SR_PHYSICS_LINK_LIBRARIES PhysXPvdSDK_static_64)
    #list(APPEND SR_PHYSICS_LINK_LIBRARIES PhysXCommon_static_64)
    #list(APPEND SR_PHYSICS_LINK_LIBRARIES PhysXFoundation_static_64)
    #list(APPEND SR_PHYSICS_LINK_LIBRARIES pthread)
    #list(APPEND SR_PHYSICS_LINK_LIBRARIES dl)
endif()
# ----------------------------------------------------------------------------------------------------------------------

if (SR_PHYSICS_STATIC_LIBRARY)
    add_library(Physics STATIC Physics.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Physics SHARED Physics.cxx)
    add_library(Physics::lib ALIAS Physics)
endif()

target_link_libraries(Physics ${SR_PHYSICS_LINK_LIBRARIES})

target_include_directories(Physics PUBLIC inc)
target_include_directories(Physics PUBLIC libs)
target_include_directories(Physics PUBLIC ${BULLET_PHYSICS_SOURCE_DIR}/src)
target_include_directories(Physics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Physics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)
target_include_directories(Physics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include/tracy/tracy)
target_include_directories(Physics PUBLIC  ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include/icu)