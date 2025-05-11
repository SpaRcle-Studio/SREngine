if (WIN32 OR ANDROID_NDK)
    set(SR_MONO_SOURCES_URL "https://github.com/SpaRcle-Studio/mono")
    set(SR_MONO_ROOT "${SR_VENV_DIR}/mono")
    set(SR_MONO_BUILD_DIR "${SR_VENV_DIR}/mono-build")

    message(STATUS "CloneMonoSources: SR_MONO_ROOT: ${SR_MONO_ROOT}")
    message(STATUS "CloneMonoSources: SR_MONO_BUILD_DIR: ${SR_MONO_BUILD_DIR}")

    if (NOT EXISTS "${SR_MONO_ROOT}")
        message(STATUS "CloneMonoSources: mono not found, cloning...")

        execute_process(
            COMMAND git clone ${SR_MONO_SOURCES_URL} ${SR_MONO_ROOT}
        )
    else()
        message(STATUS "CloneMonoSources: mono already exists, skipping clone.")
    endif()

    if (NOT EXISTS "${SR_MONO_ROOT}")
        message(FATAL_ERROR "CloneMonoSources: failed to clone mono!")
    endif()
endif()