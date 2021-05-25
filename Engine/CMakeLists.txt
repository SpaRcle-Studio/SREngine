cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Dependences/Framework)
add_subdirectory(Core)

#find_package(PythonLibs REQUIRED)
#include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(Engine main.cpp)
target_link_libraries(Engine Core Framework)#${PYTHON_LIBRARIES}

