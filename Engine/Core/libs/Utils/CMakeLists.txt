cmake_minimum_required(VERSION 3.16)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE INTERNAL "" FORCE)

set(ICU_PREBUILT_VERSION "69.1")

add_subdirectory(libs/nativefiledialog)
add_subdirectory(libs/glm)
add_subdirectory(libs/assimp)
#
#set(ICU_ROOT Z:/Repositories/icu/icu4c/source)
#find_package(ICU 61.0 COMPONENTS uc i18n REQUIRED)

if (SR_UTILS_STATIC_LIBRARY)
    add_library(Utils STATIC ICU.cxx Utils.cxx)

    if (CYGWIN)

    else()

    endif()
else()
    add_library(Utils SHARED ICU.cxx Utils.cxx)
    add_library(Utils::lib ALIAS Utils)
endif()

target_link_libraries(Utils assimp nfd)
#target_link_libraries(Utils icu)

#include_directories(Utils ${ICU_INCLUDE_DIRS})
#link_directories(Utils ${ICU_LIBRARY_DIRS})
#target_link_libraries(Utils ${ICU_LIBRARIES})

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include/icu)
target_include_directories(Utils PUBLIC inc)
target_include_directories(Utils PUBLIC libs)
target_include_directories(Utils PUBLIC libs/assimp/include)

# --------------------------------------------------------------------------------------

list(APPEND SR_UTILS_ALL_HEADERS inc/Utils/)

foreach(SR_UTILS_HEADER ${SR_UTILS_ALL_HEADERS})
    file(COPY ${SR_UTILS_HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/Utils)
endforeach()

# --------------------------------------------------------------------------------------

list(APPEND SR_UTILS_ICU_ALL_HEADERS libs/icu)

foreach(SR_UTILS_ICU_HEADER ${SR_UTILS_ICU_ALL_HEADERS})
    file(COPY ${SR_UTILS_ICU_HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include)
endforeach()