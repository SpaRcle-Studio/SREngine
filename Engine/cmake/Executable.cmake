define_property(GLOBAL PROPERTY SR_EXECUTABLE_ARGS
    BRIEF_DOCS "Executable arguments"
    FULL_DOCS "List of command line arguments to be passed to the engine executable"
)

set_property(GLOBAL PROPERTY SR_EXECUTABLE_ARGS "")

option(SR_EMSCRIPTEN_USE_PTHREADS "Use pthreads in Emscripten build" OFF)

if (ANDROID_NDK)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

    add_library(${SR_EXECUTABLE_NAME} SHARED "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Platform/Android/app/src/main/cpp/main.cpp")

    set_target_properties(sparcle PROPERTIES DEBUG_POSTFIX "")

    find_library(log-lib log)

    target_link_libraries(${SR_EXECUTABLE_NAME}
        ${log-lib}
        android
        EGL
        GLESv1_CM
    )
elseif(SR_EMSCRIPTEN)
    include(cmake/PackResourcesToBuild.cmake)
    SRPackResourcesToBuild()

    add_executable(${SR_EXECUTABLE_NAME} "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Platform/Emscripten/main.cpp")

    target_link_libraries(${SR_EXECUTABLE_NAME} Engine)
    target_include_directories(${SR_EXECUTABLE_NAME} PUBLIC "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Engine/inc")

    if (SR_EMSCRIPTEN_USE_PTHREADS)
        set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES
            LINK_FLAGS "-sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 -sPTHREAD_POOL_SIZE=8 -sFULL_ES3=1 -sUSE_PTHREADS=1 -sMODULARIZE=1 -sINITIAL_MEMORY=134217728 -sEXPORT_NAME=SREngine --preload-file ${SR_CMAKE_ROOT_BUILD_DIRECTORY}/PackedResources@/Resources -o ${SR_EXECUTABLE_NAME}.html"
        )
    else()
        set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES
            LINK_FLAGS "-sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 -sFULL_ES3=1 -sMODULARIZE=1 -sINITIAL_MEMORY=134217728 -sEXPORT_NAME=SREngine --preload-file ${SR_CMAKE_ROOT_BUILD_DIRECTORY}/PackedResources@/Resources -o ${SR_EXECUTABLE_NAME}.html"
        )
    endif()

    # Скопировать файлы после сборки
    add_custom_command(TARGET ${SR_EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SR_CMAKE_ROOT_BUILD_DIRECTORY}/Engine/${SR_EXECUTABLE_NAME}.wasm"
        "${SR_CMAKE_ROOT_BUILD_DIRECTORY}/Engine/${SR_EXECUTABLE_NAME}.js"
        "${SR_CMAKE_ROOT_BUILD_DIRECTORY}/Engine/${SR_EXECUTABLE_NAME}.data"
        "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Platform/Emscripten/Bin/"
    )
else()
    set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Platform/Desktop/main.cpp")

    if (NOT CMAKE_GENERATOR MATCHES "Visual Studio")
        set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")
    endif()

    get_property(SR_EXECUTABLE_ARGS_CONTENT GLOBAL PROPERTY SR_EXECUTABLE_ARGS)
    message(STATUS "SpaRcle Engine: adding executable arguments: ${SR_EXECUTABLE_ARGS_CONTENT}")
    add_executable(${SR_EXECUTABLE_NAME} ${SR_EXECUTABLE_ARGS_CONTENT})

    set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SR_EXECUTABLE_DIR})
    set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${SR_EXECUTABLE_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${SR_EXECUTABLE_DIR}
    )
endif()

if (NOT SR_EMSCRIPTEN)
    if (SR_ENGINE_STATIC_LIBRARY)
        target_link_libraries(${SR_EXECUTABLE_NAME} Engine)
    else()
        add_dependencies(${SR_EXECUTABLE_NAME} Engine)

        target_link_libraries(${SR_EXECUTABLE_NAME} zlibstatic)

        if (WIN32)
            target_link_libraries(${SR_EXECUTABLE_NAME} Wininet)
        endif()

        target_include_directories(${SR_EXECUTABLE_NAME} PRIVATE ${SR_ZLIB_INCLUDE_DIRS})
    endif()
endif()

if (NOT ANDROID_NDK AND NOT SR_EMSCRIPTEN)
    # TODO: implement an easy way to set if a build is 'stable' or 'latest'
    if (SR_CI_BUILD)
        set(executableType "dev")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(executableType "stable")
    else()
        set(executableType "latest")
    endif()

    if (SR_ENGINE_FLATPAK_BUILD)
        install(TARGETS ${SR_EXECUTABLE_NAME} DESTINATION /app/bin)
        install(TARGETS ${SR_EXECUTABLE_NAME} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    endif()

    if (SR_ENGINE_EXTENDED_NAME)
        if (UNIX AND NOT APPLE)
            set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${SR_EXECUTABLE_NAME}_v${SR_ENGINE_VERSION}-${executableType}_linux.${CURRENT_TARGET_ARCHITECTURE}")
        elseif (WIN32)
            set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${SR_EXECUTABLE_NAME}_v${SR_ENGINE_VERSION}-${executableType}_windows.${CURRENT_TARGET_ARCHITECTURE}")
        endif()
    else()
        set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "srengine")
    endif()
endif()