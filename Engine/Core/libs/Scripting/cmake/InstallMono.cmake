if (WIN32 OR ANDROID_NDK)
    set(SR_MONO_PREBUILD_FOR_BUILD_URL "https://github.com/SpaRcle-Studio/MonoWindows.git")
    set(SR_MONO_PREBUILD_DIR "${SR_VENV_DIR}/MonoPrebuildForBuild")

    message(STATUS "InstallMono: SR_MONO_PREBUILD_FOR_BUILD_URL: ${SR_MONO_PREBUILD_FOR_BUILD_URL}")
    message(STATUS "InstallMono: SR_MONO_PREBUILD_DIR: ${SR_MONO_PREBUILD_DIR}")

    if (NOT EXISTS "${SR_MONO_PREBUILD_DIR}")
        message(STATUS "InstallMono: mono not found, cloning...")

        execute_process(
            COMMAND git clone ${SR_MONO_PREBUILD_FOR_BUILD_URL} ${SR_MONO_PREBUILD_DIR}
        )
    else()
        message(STATUS "InstallMono: mono already exists, skipping clone.")
    endif()

    if (NOT EXISTS "${SR_MONO_PREBUILD_DIR}")
        message(FATAL_ERROR "InstallMono: failed to clone mono!")
    endif()
endif()