if(WIN32 OR ANDROID_NDK)
    set(SR_BASH_EXECUTABLE "${SR_CYGWIN_INSTALL_DIR}/bin/bash.exe")
else()
    set(SR_BASH_EXECUTABLE "/bin/bash")
endif()

message(STATUS "SR_BASH_EXECUTABLE: ${SR_BASH_EXECUTABLE}")

file(MAKE_DIRECTORY "${SR_MONO_BUILD_DIR}")
message(STATUS "SR_MONO_BUILD_DIR: ${SR_MONO_BUILD_DIR}")
message(STATUS "SR_MONO_ROOT: ${SR_MONO_ROOT}")

message(STATUS "Building mono... This may take a while.")

set(Mono_INCLUDE_DIR "${SR_MONO_ROOT}/msvc/include")
set(Mono_LIBRARY "${SR_MONO_ROOT}/msvc/build/sgen/x64/lib/Release/libmono-static-sgen.lib")

execute_process(
    COMMAND ${SR_PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/python/build_mono.py"
    --src "${SR_MONO_ROOT}"
    --build "${SR_MONO_BUILD_DIR}"
    --jobs $ENV{NUMBER_OF_PROCESSORS}
    --bash "${SR_BASH_EXECUTABLE}"
    --python "${SR_PYTHON_EXECUTABLE}"
    --venv "${SR_VENV_DIR}"
    --library "${Mono_LIBRARY}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
)

if (NOT result EQUAL "0")
    message(FATAL_ERROR "Failed to build mono with error:\n${error_output}")
else()
    message(STATUS "Mono build completed successfully:\n${output}")
endif()