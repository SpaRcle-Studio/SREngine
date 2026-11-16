include_guard(GLOBAL)

set(SR_VULKAN_SDK_VERSION "1.4.363.0" CACHE STRING "Vulkan SDK version")
option(SR_AUTO_INSTALL_VULKAN_SDK "Download and install Vulkan SDK automatically" ON)

# Locate the repository root, regardless of build directory.
set(SR_VULKAN_SDK_BASE "${SR_CMAKE_VENV_DIRECTORY}/VulkanSDK")
set(SR_VULKAN_SDK_ROOT "${SR_VULKAN_SDK_BASE}/${SR_VULKAN_SDK_VERSION}")

if(WIN32 AND NOT ANDROID)
    set(SR_VULKAN_SDK_HOME "${SR_VULKAN_SDK_ROOT}")
    set(SR_VULKAN_SDK_URL "https://sdk.lunarg.com/sdk/download/${SR_VULKAN_SDK_VERSION}/windows/vulkansdk-windows-X64-${SR_VULKAN_SDK_VERSION}.exe")
    set(SR_VULKAN_SDK_ARCHIVE "${SR_VULKAN_SDK_BASE}/vulkansdk-${SR_VULKAN_SDK_VERSION}.exe")
    set(SR_VULKAN_HEADER "${SR_VULKAN_SDK_HOME}/Include/vulkan/vulkan.h")
    set(SR_VULKAN_LIBRARY "${SR_VULKAN_SDK_HOME}/Lib/vulkan-1.lib")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SR_VULKAN_SDK_HOME "${SR_VULKAN_SDK_ROOT}/x86_64")
    set(SR_VULKAN_SDK_URL "https://sdk.lunarg.com/sdk/download/${SR_VULKAN_SDK_VERSION}/linux/vulkan-sdk.tar.xz")
    set(SR_VULKAN_SDK_ARCHIVE "${SR_VULKAN_SDK_BASE}/vulkansdk-${SR_VULKAN_SDK_VERSION}.tar.xz")
    set(SR_VULKAN_HEADER "${SR_VULKAN_SDK_HOME}/include/vulkan/vulkan.h")
    set(SR_VULKAN_LIBRARY "${SR_VULKAN_SDK_HOME}/lib/libvulkan.so")
else()
    message(STATUS "[SpaRcle Engine] Vulkan SDK bootstrap skipped for ${CMAKE_SYSTEM_NAME}")
    return()
endif()

# Verify the SDK, not merely its directory.
if(NOT EXISTS "${SR_VULKAN_HEADER}" OR NOT EXISTS "${SR_VULKAN_LIBRARY}")

    if(NOT SR_AUTO_INSTALL_VULKAN_SDK)
        message(FATAL_ERROR "[SpaRcle Engine] Vulkan SDK ${SR_VULKAN_SDK_VERSION} not found")
    endif()

    file(MAKE_DIRECTORY "${SR_VULKAN_SDK_BASE}")

    if(NOT EXISTS "${SR_VULKAN_SDK_ARCHIVE}")
        message(STATUS "[SpaRcle Engine] Downloading Vulkan SDK ${SR_VULKAN_SDK_VERSION}...")

        file(DOWNLOAD
            "${SR_VULKAN_SDK_URL}"
            "${SR_VULKAN_SDK_ARCHIVE}"
            STATUS SR_VULKAN_DOWNLOAD_STATUS
            SHOW_PROGRESS
            TLS_VERIFY ON
        )

        list(GET SR_VULKAN_DOWNLOAD_STATUS 0 SR_VULKAN_DOWNLOAD_CODE)

        if(NOT SR_VULKAN_DOWNLOAD_CODE EQUAL 0)
            file(REMOVE "${SR_VULKAN_SDK_ARCHIVE}")
            message(FATAL_ERROR "[SpaRcle Engine] Vulkan SDK download failed: ${SR_VULKAN_DOWNLOAD_STATUS}")
        endif()
    endif()

    message(STATUS "[SpaRcle Engine] Installing Vulkan SDK...")

    if(WIN32)
        execute_process(
            COMMAND
            "${SR_VULKAN_SDK_ARCHIVE}"
            --root "${SR_VULKAN_SDK_HOME}"
            --accept-licenses
            --default-answer
            --confirm-command
            install
            copy_only=1
            RESULT_VARIABLE SR_VULKAN_INSTALL_RESULT
        )

        if(NOT SR_VULKAN_INSTALL_RESULT STREQUAL "0")
            message(FATAL_ERROR "[SpaRcle Engine] Vulkan SDK installation failed: ${SR_VULKAN_INSTALL_RESULT}")
        endif()

    else()
        file(ARCHIVE_EXTRACT INPUT "${SR_VULKAN_SDK_ARCHIVE}" DESTINATION "${SR_VULKAN_SDK_BASE}")
    endif()
endif()

if(NOT EXISTS "${SR_VULKAN_HEADER}" OR NOT EXISTS "${SR_VULKAN_LIBRARY}")
    message(FATAL_ERROR "[SpaRcle Engine] Vulkan SDK installation is incomplete: ${SR_VULKAN_SDK_HOME}")
endif()

# Configure Vulkan SDK discovery for this CMake process.
set(ENV{VULKAN_SDK} "${SR_VULKAN_SDK_HOME}")
set(ENV{VK_SDK_PATH} "${SR_VULKAN_SDK_HOME}")

set(Vulkan_ROOT "${SR_VULKAN_SDK_HOME}")
set(Vulkan_ROOT "${SR_VULKAN_SDK_HOME}" CACHE PATH "Vulkan SDK root" FORCE)

list(PREPEND CMAKE_PREFIX_PATH "${SR_VULKAN_SDK_HOME}")

if(WIN32)
    set(ENV{PATH} "${SR_VULKAN_SDK_HOME}/Bin;$ENV{PATH}")
    set(ENV{VK_ADD_LAYER_PATH} "${SR_VULKAN_SDK_HOME}/Bin")
else()
    set(ENV{PATH} "${SR_VULKAN_SDK_HOME}/bin:$ENV{PATH}")
    set(ENV{VK_ADD_LAYER_PATH} "${SR_VULKAN_SDK_HOME}/share/vulkan/explicit_layer.d")
    list(PREPEND CMAKE_PREFIX_PATH "${SR_VULKAN_SDK_HOME}/lib/VulkanLoader")
endif()

# Force FindVulkan to use the local SDK.
set(Vulkan_INCLUDE_DIR "${SR_VULKAN_SDK_HOME}/$<IF:$<BOOL:${WIN32}>,Include,include>" CACHE PATH "" FORCE)

# Use ordinary paths rather than generator expressions.
if(WIN32)
    set(Vulkan_INCLUDE_DIR "${SR_VULKAN_SDK_HOME}/Include" CACHE PATH "" FORCE)
else()
    set(Vulkan_INCLUDE_DIR "${SR_VULKAN_SDK_HOME}/include" CACHE PATH "" FORCE)
endif()

set(Vulkan_LIBRARY "${SR_VULKAN_LIBRARY}" CACHE PATH "" FORCE)

find_package(Vulkan REQUIRED)

message(STATUS "[SpaRcle Engine] Vulkan SDK: ${SR_VULKAN_SDK_HOME}")
message(STATUS "[SpaRcle Engine] Vulkan include: ${Vulkan_INCLUDE_DIR}")
message(STATUS "[SpaRcle Engine] Vulkan library: ${Vulkan_LIBRARY}")