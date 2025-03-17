if (WIN32 OR ANDROID_NDK)
    set(SR_MONO_BUILD_TOOL_URL "https://github.com/SpaRcle-Studio/MonoBuildTool.git")
    set(SR_MONO_BUILD_TOOL_DIR "${SR_VENV_DIR}/MonoBuildTool")

    message(STATUS "InstallMonoBuildTool: SR_MONO_BUILD_TOOL_URL: ${SR_MONO_BUILD_TOOL_URL}")
    message(STATUS "InstallMonoBuildTool: SR_MONO_BUILD_TOOL_DIR: ${SR_MONO_BUILD_TOOL_DIR}")

    if (NOT EXISTS "${SR_MONO_BUILD_TOOL_DIR}")
        message(STATUS "InstallMonoBuildTool: mono not found, cloning...")

        execute_process(
            COMMAND git clone ${SR_MONO_BUILD_TOOL_URL} ${SR_MONO_BUILD_TOOL_DIR}
        )
    else()
        message(STATUS "InstallMonoBuildTool: mono already exists, skipping clone.")
    endif()

    if (NOT EXISTS "${SR_MONO_BUILD_TOOL_DIR}")
        message(FATAL_ERROR "InstallMonoBuildTool: failed to clone mono!")
    endif()
endif()