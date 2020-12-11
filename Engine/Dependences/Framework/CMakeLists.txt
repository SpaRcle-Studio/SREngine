cmake_minimum_required(VERSION 3.16)
project(Framework)

# Переменная дириктории исходного кода данного фреймворка
set(FRAMEWORK_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Depends/inc/glm)
add_subdirectory(Depends/glfw)
add_subdirectory(Depends/glew/build/cmake)

# Включаем вспомогательные файлы
include(Audio.cmake)
include(Graphics.cmake)
include(Helper.cmake)
include(Physics.cmake)

find_package(OpenGL REQUIRED)

# Добавляем библиотеку фреймворка
add_library(Framework STATIC ${AUDIO_SRC} ${GRAPHICS_SRC} ${HELPER_SRC} ${PHYSICS_SRC})
target_link_libraries(Framework opengl32 glfw glew)
if(WIN32)
    if(MSVC)

    else()
        target_link_libraries(Framework -lpsapi opengl32 glfw glew)
    endif()
endif()

# Устанавливаем директории
target_include_directories(Framework
        PUBLIC ${AUDIO_INC_PUBLIC} ${GRAPHICS_INC_PUBLIC} ${HELPER_INC_PUBLIC} ${PHYSICS_INC_PUBLIC}
        PRIVATE ${AUDIO_INC_PRIVATE} ${GRAPHICS_INC_PRIVATE} ${HELPER_INC_PRIVATE} ${PHYSICS_INC_PRIVATE}
        INSTANCE ${AUDIO_INC_INSTANCE} ${GRAPHICS_INC_INSTANCE} ${HELPER_INC_INSTANCE} ${PHYSICS_INC_INSTANCE})