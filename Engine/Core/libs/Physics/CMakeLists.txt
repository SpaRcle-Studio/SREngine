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
    add_compile_definitions(SR_PHYSICS_USE_PHYSX)

    set(PHYSX_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/PhysX/physx)
    set(PHYSX_INCLUDE_DIRS ${PHYSX_ROOT_DIR}/include/ ${PHYSX_ROOT_DIR}/../pxshared/include/)
    set(CMAKEMODULES_PATH ${PHYSX_ROOT_DIR}/../externals/cmakemodules)

    #if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    #    set(CMAKE_CONFIGURATION_TYPES "debug")
    #else()
    #    set(CMAKE_CONFIGURATION_TYPES "release")
    #endif()

    if (WIN32)
        set(TARGET_BUILD_PLATFORM "windows")
        set(NV_USE_DEBUG_WINCRT ON CACHE BOOL "Use the debug version of the CRT")
    else()
        if (ANDROID_NDK)
            set(TARGET_BUILD_PLATFORM "android")
        else()
            message("Unsupported platform!")
        endif()
    endif()

    set(PX_BUILDSNIPPETS OFF CACHE BOOL "Generate the snippets")
    set(PX_USE_PLATFORM_MAP_FLAG OFF CACHE BOOL "Use platform MAP flag")
    set(PX_BUILDPUBLICSAMPLES OFF CACHE BOOL "Generate the samples projects")

    if (ANDROID_NDK)
        set(PX_GENERATE_STATIC_LIBRARIES ON CACHE BOOL "Generate static libraries")
    else()
        set(PX_GENERATE_STATIC_LIBRARIES OFF CACHE BOOL "Generate static libraries")
    endif()

    set(PX_FLOAT_POINT_PRECISE_MATH OFF CACHE BOOL "Float point precise math")
    set(NV_USE_STATIC_WINCRT OFF CACHE BOOL "Use the statically linked windows CRT")
    set(PXSHARED_PATH ${PHYSX_ROOT_DIR}/../pxshared)
    set(PXSHARED_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
    set(CMAKEMODULES_VERSION "1.27")
    set(CMAKEMODULES_PATH ${PHYSX_ROOT_DIR}/../externals/cmakemodules)
    set(PX_OUTPUT_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/extern/physx)
    set(PX_OUTPUT_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/extern/physx)

    add_subdirectory(${PHYSX_ROOT_DIR}/compiler/public)

    set(PHYSX_LIBRARIES
        PhysXFoundation
        LowLevel
        LowLevelAABB
        LowLevelDynamics
        PhysX
        PhysXCharacterKinematic
        PhysXCommon
        PhysXCooking
        PhysXExtensions
        PhysXVehicle
        SceneQuery
        SimulationController
        FastXml
        PhysXPvdSDK
        PhysXTask
    )

    if(MSVC)
        foreach(LIBRARY_ITERATE ${PHYSX_LIBRARIES})
            target_compile_options(${LIBRARY_ITERATE} PUBLIC "/wd5054;")
            target_compile_options(${LIBRARY_ITERATE} PUBLIC "/wd5055;")
        endforeach()
    else()
        foreach(LIBRARY_ITERATE ${PHYSX_LIBRARIES})
            target_compile_options(${LIBRARY_ITERATE} PRIVATE -Wall -Wextra -Wpedantic -Werror
                    -Wno-unused-private-field
                    -Wno-unused-local-typedefs
                    -Wno-gnu-statement-expression
                    -Wno-bitwise-instead-of-logical
                    -Wno-unused-but-set-variable
                    -Wno-deprecated-copy-with-user-provided-copy
                    -Wno-dtor-name
            )
        endforeach()
    endif()

    list(APPEND SR_PHYSICS_LINK_LIBRARIES ${PHYSX_LIBRARIES})
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