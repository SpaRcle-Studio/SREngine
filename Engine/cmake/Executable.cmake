define_property(GLOBAL PROPERTY SR_EXECUTABLE_ARGS
    BRIEF_DOCS "Executable arguments"
    FULL_DOCS "List of command line arguments to be passed to the engine executable"
)

set_property(GLOBAL PROPERTY SR_EXECUTABLE_ARGS "")

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

else()
    set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Platform/Desktop/main.cpp")

    if (NOT CMAKE_GENERATOR MATCHES "Visual Studio")
        set_property(GLOBAL APPEND PROPERTY SR_EXECUTABLE_ARGS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")
    endif()

    get_property(SR_EXECUTABLE_ARGS_CONTENT GLOBAL PROPERTY SR_EXECUTABLE_ARGS)
    message(STATUS "SpaRcle Engine: adding executable arguments: ${SR_EXECUTABLE_ARGS_CONTENT}")
    add_executable(${SR_EXECUTABLE_NAME} ${SR_EXECUTABLE_ARGS_CONTENT})
    set_target_properties(${SR_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SR_EXECUTABLE_DIR})
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
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
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