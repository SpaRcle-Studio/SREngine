cmake_minimum_required(VERSION 3.16)
project(Physics)

set(CMAKE_CXX_STANDARD 20)

add_definitions(
    -DMODPLUG_STATIC
    -DFLAC__NO_DLL
)

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

if (SR_PHYSICS_STATIC_LIBRARY)
    add_library(Physics STATIC Physics.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Physics SHARED Physics.cxx)
    add_library(Physics::lib ALIAS Physics)
endif()

target_link_libraries(Physics
    Bullet3Common
    BulletSoftBody
    BulletInverseDynamicsUtils
    BulletInverseDynamics
    BulletDynamics
    BulletCollision
    LinearMath
)

target_include_directories(Physics PUBLIC inc)
target_include_directories(Physics PUBLIC libs)
target_include_directories(Physics PUBLIC ${BULLET_PHYSICS_SOURCE_DIR}/src)
target_include_directories(Physics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Utils/include)
target_include_directories(Physics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/libs)
