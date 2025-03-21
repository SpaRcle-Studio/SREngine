set(SR_MONO_PREBUILD_URL "https://github.com/SpaRcle-Studio/MonoPrebuild.git")
set(SR_MONO_PREBUILD_DIR "${SR_VENV_DIR}/MonoPrebuild")

message(STATUS "CloneMonoPrebuild: SR_MONO_PREBUILD_URL: ${SR_MONO_PREBUILD_URL}")
message(STATUS "CloneMonoPrebuild: SR_MONO_PREBUILD_DIR: ${SR_MONO_PREBUILD_DIR}")

if (NOT EXISTS "${SR_MONO_PREBUILD_DIR}")
    message(STATUS "CloneMonoPrebuild: mono not found, cloning...")

    execute_process(
        COMMAND git clone ${SR_MONO_PREBUILD_URL} ${SR_MONO_PREBUILD_DIR}
    )
else()
    message(STATUS "CloneMonoPrebuild: mono already exists, skipping clone.")
endif()

if (NOT EXISTS "${SR_MONO_PREBUILD_DIR}")
    message(FATAL_ERROR "CloneMonoPrebuild: failed to clone mono!")
endif()

set(MONO_INCLUDE_DIRS "${SR_MONO_PREBUILD_DIR}/include/mono-2.0")

if (WIN32)
    set(MONO_LIBRARIES "${SR_MONO_PREBUILD_DIR}/lib/libmono-static-sgen.lib")
else()
    set(MONO_LIBRARIES "${SR_MONO_PREBUILD_DIR}/lib/libmonosgen-2.0.a")
endif()