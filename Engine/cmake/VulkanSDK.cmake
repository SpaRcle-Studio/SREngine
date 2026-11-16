include_guard(GLOBAL)

set(SR_VULKAN_SDK_VERSION "1.4.363.0" CACHE STRING "Vulkan SDK version")
option(SR_AUTO_INSTALL_VULKAN_SDK "Download and install Vulkan SDK automatically" ON)

if(NOT DEFINED SR_CMAKE_VENV_DIRECTORY OR SR_CMAKE_VENV_DIRECTORY STREQUAL "")
    message(FATAL_ERROR "[SpaRcle Engine] SR_CMAKE_VENV_DIRECTORY is not defined!")
endif()

set(SR_VULKAN_SDK_BASE "${SR_CMAKE_VENV_DIRECTORY}/VulkanSDK")
set(SR_VULKAN_SDK_ROOT "${SR_VULKAN_SDK_BASE}/${SR_VULKAN_SDK_VERSION}")

if(WIN32 AND NOT ANDROID)
    set(SR_VULKAN_SDK_HOME "${SR_VULKAN_SDK_ROOT}")
    set(SR_VULKAN_SDK_URL "https://sdk.lunarg.com/sdk/download/${SR_VULKAN_SDK_VERSION}/windows/vulkansdk-windows-X64-${SR_VULKAN_SDK_VERSION}.exe")
    set(SR_VULKAN_SDK_ARCHIVE "${SR_VULKAN_SDK_BASE}/vulkansdk-${SR_VULKAN_SDK_VERSION}.exe")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SR_VULKAN_SDK_HOME "${SR_VULKAN_SDK_ROOT}/x86_64")
    set(SR_VULKAN_SDK_URL "https://sdk.lunarg.com/sdk/download/${SR_VULKAN_SDK_VERSION}/linux/vulkan-sdk.tar.xz")
    set(SR_VULKAN_SDK_ARCHIVE "${SR_VULKAN_SDK_BASE}/vulkansdk-${SR_VULKAN_SDK_VERSION}.tar.xz")
else()
    message(STATUS "[SpaRcle Engine] Vulkan SDK bootstrap skipped for ${CMAKE_SYSTEM_NAME}")
    return()
endif()

file(MAKE_DIRECTORY "${SR_VULKAN_SDK_BASE}")

file(LOCK "${SR_VULKAN_SDK_BASE}/bootstrap.lock" GUARD PROCESS TIMEOUT 600 RESULT_VARIABLE SR_VULKAN_LOCK_RESULT)

if(NOT SR_VULKAN_LOCK_RESULT STREQUAL "0")
    message(FATAL_ERROR "[SpaRcle Engine] Failed to lock Vulkan SDK: ${SR_VULKAN_LOCK_RESULT}")
endif()

function(sr_find_vulkan_sdk_home OUTPUT)
    set(${OUTPUT} "" PARENT_SCOPE)

    if(WIN32)
        if(EXISTS "${SR_VULKAN_SDK_ROOT}/Include/vulkan/vulkan.h" AND EXISTS "${SR_VULKAN_SDK_ROOT}/Lib/vulkan-1.lib")
            set(${OUTPUT} "${SR_VULKAN_SDK_ROOT}" PARENT_SCOPE)
        endif()
        return()
    endif()

    set(_candidates
        "${SR_VULKAN_SDK_ROOT}/x86_64"
        "${SR_VULKAN_SDK_ROOT}"
        "${SR_VULKAN_SDK_BASE}/x86_64"
    )

    foreach(_candidate IN LISTS _candidates)
        if(EXISTS "${_candidate}/include/vulkan/vulkan.h")
            set(${OUTPUT} "${_candidate}" PARENT_SCOPE)
            return()
        endif()
    endforeach()

    file(GLOB_RECURSE _headers LIST_DIRECTORIES FALSE "${SR_VULKAN_SDK_BASE}/vulkan.h")

    foreach(_header IN LISTS _headers)
        if(_header MATCHES "/include/vulkan/vulkan\\.h$")
            get_filename_component(_vulkan_dir "${_header}" DIRECTORY)
            get_filename_component(_include_dir "${_vulkan_dir}" DIRECTORY)
            get_filename_component(_home "${_include_dir}" DIRECTORY)
            set(${OUTPUT} "${_home}" PARENT_SCOPE)
            return()
        endif()
    endforeach()
endfunction()

sr_find_vulkan_sdk_home(SR_VULKAN_FOUND_HOME)

if(NOT SR_VULKAN_FOUND_HOME)
    if(NOT SR_AUTO_INSTALL_VULKAN_SDK)
        message(FATAL_ERROR "[SpaRcle Engine] Vulkan SDK ${SR_VULKAN_SDK_VERSION} not found!")
    endif()

    if(NOT EXISTS "${SR_VULKAN_SDK_ARCHIVE}")
        message(STATUS "[SpaRcle Engine] Downloading Vulkan SDK ${SR_VULKAN_SDK_VERSION}...")

        set(SR_VULKAN_DOWNLOAD_SUCCESS FALSE)

        foreach(SR_ATTEMPT RANGE 1 3)
            message(STATUS "[SpaRcle Engine] Download attempt ${SR_ATTEMPT}/3")

            file(DOWNLOAD "${SR_VULKAN_SDK_URL}" "${SR_VULKAN_SDK_ARCHIVE}"
                STATUS SR_VULKAN_DOWNLOAD_STATUS
                LOG SR_VULKAN_DOWNLOAD_LOG
                TLS_VERIFY ON
                INACTIVITY_TIMEOUT 60
                TIMEOUT 600
            )

            list(GET SR_VULKAN_DOWNLOAD_STATUS 0 SR_DOWNLOAD_CODE)

            if(SR_DOWNLOAD_CODE EQUAL 0)
                set(SR_VULKAN_DOWNLOAD_SUCCESS TRUE)
                break()
            endif()

            message(WARNING "[SpaRcle Engine] Download failed: ${SR_VULKAN_DOWNLOAD_STATUS}")
            file(REMOVE "${SR_VULKAN_SDK_ARCHIVE}")
        endforeach()

        if(NOT SR_VULKAN_DOWNLOAD_SUCCESS)
            find_program(SR_VULKAN_CURL_EXECUTABLE NAMES curl)

            if(SR_VULKAN_CURL_EXECUTABLE)
                message(STATUS "[SpaRcle Engine] Trying system curl...")

                execute_process(
                    COMMAND "${SR_VULKAN_CURL_EXECUTABLE}" --fail --location --retry 5 --retry-all-errors --retry-delay 5 --connect-timeout 30 --max-time 600 --output "${SR_VULKAN_SDK_ARCHIVE}" "${SR_VULKAN_SDK_URL}"
                    RESULT_VARIABLE SR_VULKAN_CURL_RESULT
                )

                if(SR_VULKAN_CURL_RESULT EQUAL 0)
                    set(SR_VULKAN_DOWNLOAD_SUCCESS TRUE)
                endif()
            endif()
        endif()

        if(NOT SR_VULKAN_DOWNLOAD_SUCCESS)
            file(REMOVE "${SR_VULKAN_SDK_ARCHIVE}")
            message(FATAL_ERROR "[SpaRcle Engine] Failed to download Vulkan SDK from ${SR_VULKAN_SDK_URL}")
        endif()
    endif()

    message(STATUS "[SpaRcle Engine] Installing Vulkan SDK...")

    if(WIN32)
        file(MAKE_DIRECTORY "${SR_VULKAN_SDK_ROOT}")

        execute_process(
            COMMAND "${SR_VULKAN_SDK_ARCHIVE}" --root "${SR_VULKAN_SDK_ROOT}" --accept-licenses --default-answer --confirm-command install copy_only=1
            RESULT_VARIABLE SR_VULKAN_INSTALL_RESULT
        )

        if(NOT SR_VULKAN_INSTALL_RESULT STREQUAL "0")
            message(FATAL_ERROR "[SpaRcle Engine] Vulkan SDK installation failed: ${SR_VULKAN_INSTALL_RESULT}")
        endif()
    else()
        file(ARCHIVE_EXTRACT INPUT "${SR_VULKAN_SDK_ARCHIVE}" DESTINATION "${SR_VULKAN_SDK_BASE}")
    endif()

    sr_find_vulkan_sdk_home(SR_VULKAN_FOUND_HOME)

    if(NOT SR_VULKAN_FOUND_HOME)
        message(FATAL_ERROR "[SpaRcle Engine] Vulkan SDK installation is incomplete! Directory: ${SR_VULKAN_SDK_BASE}")
    endif()
endif()

set(SR_VULKAN_SDK_HOME "${SR_VULKAN_FOUND_HOME}")

set(ENV{VULKAN_SDK} "${SR_VULKAN_SDK_HOME}")
set(ENV{VK_SDK_PATH} "${SR_VULKAN_SDK_HOME}")

set(Vulkan_ROOT "${SR_VULKAN_SDK_HOME}" CACHE PATH "Vulkan SDK root" FORCE)
list(PREPEND CMAKE_PREFIX_PATH "${SR_VULKAN_SDK_HOME}")

if(WIN32)
    set(Vulkan_INCLUDE_DIR "${SR_VULKAN_SDK_HOME}/Include" CACHE PATH "Vulkan include directory" FORCE)
    set(Vulkan_LIBRARY "${SR_VULKAN_SDK_HOME}/Lib/vulkan-1.lib" CACHE FILEPATH "Vulkan loader library" FORCE)

    set(ENV{PATH} "${SR_VULKAN_SDK_HOME}/Bin;$ENV{PATH}")
    set(ENV{VK_ADD_LAYER_PATH} "${SR_VULKAN_SDK_HOME}/Bin")
else()
    set(Vulkan_INCLUDE_DIR "${SR_VULKAN_SDK_HOME}/include" CACHE PATH "Vulkan include directory" FORCE)

    unset(SR_VULKAN_LOCAL_LIBRARY CACHE)
    unset(SR_VULKAN_LOCAL_LIBRARY)

    find_library(SR_VULKAN_LOCAL_LIBRARY NAMES vulkan PATHS "${SR_VULKAN_SDK_HOME}/lib" "${SR_VULKAN_SDK_HOME}/lib64" NO_DEFAULT_PATH)

    if(SR_VULKAN_LOCAL_LIBRARY)
        set(Vulkan_LIBRARY "${SR_VULKAN_LOCAL_LIBRARY}" CACHE FILEPATH "Vulkan loader library" FORCE)
    else()
        unset(Vulkan_LIBRARY CACHE)
        unset(Vulkan_LIBRARY)

        find_library(SR_VULKAN_SYSTEM_LIBRARY NAMES vulkan)

        if(NOT SR_VULKAN_SYSTEM_LIBRARY)
            message(FATAL_ERROR "[SpaRcle Engine] Vulkan loader library not found. Install libvulkan-dev or provide a Vulkan loader.")
        endif()

        set(Vulkan_LIBRARY "${SR_VULKAN_SYSTEM_LIBRARY}" CACHE FILEPATH "Vulkan loader library" FORCE)
    endif()

    set(ENV{PATH} "${SR_VULKAN_SDK_HOME}/bin:$ENV{PATH}")
    set(ENV{VK_ADD_LAYER_PATH} "${SR_VULKAN_SDK_HOME}/share/vulkan/explicit_layer.d")

    list(PREPEND CMAKE_PREFIX_PATH "${SR_VULKAN_SDK_HOME}/lib/VulkanLoader")
endif()

find_package(Vulkan REQUIRED)

message(STATUS "[SpaRcle Engine] Vulkan SDK: ${SR_VULKAN_SDK_HOME}")
message(STATUS "[SpaRcle Engine] Vulkan include: ${Vulkan_INCLUDE_DIR}")
message(STATUS "[SpaRcle Engine] Vulkan library: ${Vulkan_LIBRARY}")
