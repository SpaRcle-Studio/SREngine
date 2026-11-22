# Created by OpenAI Codex on 22.11.2026.

# This bootstrap is host-only and is called only when system OpenCL was not found.
function(sr_install_texture_opencl)
    if(NOT SR_CMAKE_VENV_DIRECTORY)
        message(FATAL_ERROR "[SpaRcle Engine] OpenCL bootstrap requires SR_CMAKE_VENV_DIRECTORY")
    endif()
    find_package(Git REQUIRED)
    set(SR_OPENCL_VERSION "v2024.10.24")
    set(SR_OPENCL_ROOT "${SR_CMAKE_VENV_DIRECTORY}/OpenCL/${SR_OPENCL_VERSION}")
    file(MAKE_DIRECTORY "${SR_OPENCL_ROOT}")
    file(LOCK "${SR_OPENCL_ROOT}/install.lock" GUARD FUNCTION TIMEOUT 180)
    foreach(SR_OPENCL_COMPONENT IN ITEMS OpenCL-Headers OpenCL-ICD-Loader)
        set(SR_OPENCL_SOURCE "${SR_OPENCL_ROOT}/${SR_OPENCL_COMPONENT}")
        if(NOT EXISTS "${SR_OPENCL_SOURCE}/CMakeLists.txt")
            message(STATUS "[SpaRcle Engine] Installing ${SR_OPENCL_COMPONENT} ${SR_OPENCL_VERSION} in .venv...")
            set(SR_OPENCL_STAGING "${SR_OPENCL_SOURCE}.download")
            foreach(SR_OPENCL_ATTEMPT RANGE 1 3)
                file(REMOVE_RECURSE "${SR_OPENCL_STAGING}")
                execute_process(
                    COMMAND "${CMAKE_COMMAND}" -E env GIT_TERMINAL_PROMPT=0
                        "${GIT_EXECUTABLE}" -c advice.detachedHead=false clone --depth 1 --branch "${SR_OPENCL_VERSION}"
                        "https://github.com/KhronosGroup/${SR_OPENCL_COMPONENT}.git" "${SR_OPENCL_STAGING}"
                    RESULT_VARIABLE SR_OPENCL_RESULT
                    ERROR_VARIABLE SR_OPENCL_ERROR
                    TIMEOUT 180)
                if(SR_OPENCL_RESULT STREQUAL "0")
                    break()
                endif()
                message(STATUS "[SpaRcle Engine] OpenCL download attempt ${SR_OPENCL_ATTEMPT}/3 failed: ${SR_OPENCL_ERROR}")
            endforeach()
            if(NOT SR_OPENCL_RESULT STREQUAL "0")
                file(REMOVE_RECURSE "${SR_OPENCL_STAGING}")
                message(FATAL_ERROR "[SpaRcle Engine] OpenCL SDK download failed: ${SR_OPENCL_ERROR}. Retry configuration, or disable SR_TEXTURE_USE_OPENCL for CPU encoding.")
            endif()
            file(RENAME "${SR_OPENCL_STAGING}" "${SR_OPENCL_SOURCE}")
        endif()
    endforeach()

    # The binary directories must differ for separate generators, toolchains and checkouts.
    string(SHA256 SR_OPENCL_BUILD_KEY "${CMAKE_BINARY_DIR};${CMAKE_C_COMPILER};${CMAKE_GENERATOR};${CMAKE_SYSTEM_PROCESSOR};${CMAKE_SIZEOF_VOID_P}")
    string(SUBSTRING "${SR_OPENCL_BUILD_KEY}" 0 16 SR_OPENCL_BUILD_KEY)
    set(SR_OPENCL_BINARY "${SR_OPENCL_ROOT}/build/${SR_OPENCL_BUILD_KEY}")
    set(OPENCL_ICD_LOADER_HEADERS_DIR "${SR_OPENCL_ROOT}/OpenCL-Headers" CACHE PATH "Local OpenCL headers" FORCE)
    set(OPENCL_ICD_LOADER_BUILD_SHARED_LIBS ON CACHE BOOL "Build the local OpenCL ICD loader" FORCE)
    set(OPENCL_ICD_LOADER_BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(ENABLE_OPENCL_LAYERS OFF CACHE BOOL "" FORCE)
    set(ENABLE_OPENCL_LAYERINFO OFF CACHE BOOL "" FORCE)
    add_subdirectory("${SR_OPENCL_ROOT}/OpenCL-ICD-Loader" "${SR_OPENCL_BINARY}" EXCLUDE_FROM_ALL)
    set_target_properties(OpenCL PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        RUNTIME_OUTPUT_DIRECTORY "${SR_OPENCL_BINARY}/sdk/$<CONFIG>/bin"
        LIBRARY_OUTPUT_DIRECTORY "${SR_OPENCL_BINARY}/sdk/$<CONFIG>/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${SR_OPENCL_BINARY}/sdk/$<CONFIG>/lib")
    if(WIN32)
        add_custom_command(TARGET Engine POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${SR_EXECUTABLE_DIR}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:OpenCL>" "${SR_EXECUTABLE_DIR}"
            VERBATIM)
    endif()
    message(STATUS "[SpaRcle Engine] Texture export: using local OpenCL SDK at ${SR_OPENCL_ROOT}")
endfunction()
