# We need to ensure that Python is installed as well as the required packages.

set(SR_VENV_DIR "${PROJECT_SOURCE_DIR}/../.venv")

set(SR_PYTHON_REQUIREMENTS_PATH "${PROJECT_SOURCE_DIR}/../CI/requirements.txt")
# read requirements.txt and set the SR_PYTHON_REQUIREMENTS variable
file(STRINGS "${SR_PYTHON_REQUIREMENTS_PATH}" __PYTHON_REQUIREMENTS)
# remove all lines that start with # or are empty
foreach(line ${__PYTHON_REQUIREMENTS})
    string(REGEX MATCH "^[^#].*" line ${line})
    if (NOT line STREQUAL "")
        list(APPEND SR_PYTHON_REQUIREMENTS "${line}")
    endif()
endforeach()

if (SR_HOST_SYSTEM_UNIX)
    find_program(PYTHON_EXECUTABLE NAMES python3 python)

    if (PYTHON_EXECUTABLE)
       message(STATUS "InstallPython: Python executable found: ${PYTHON_EXECUTABLE}")
    else()
        message(FATAL_ERROR "InstallPython: Python executable not found. Please install Python.")
    endif()

    message(STATUS "InstallPython: creating virtual environment at: ${PROJECT_SOURCE_DIR}/../")

    execute_process(
        COMMAND ${PYTHON_EXECUTABLE} -m venv ${PROJECT_SOURCE_DIR}/../.venv
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output
    )

    if (NOT result EQUAL "0")
        message(FATAL_ERROR "InstallPython: failed to create virtual environment! ${error_output}")
    endif()

    set(SR_PYTHON_EXECUTABLE "${PROJECT_SOURCE_DIR}/../.venv/bin/python")
elseif (NOT SR_PYTHON_EXECUTABLE)
    message(STATUS "InstallPython: Python not found.")

    set(SR_PYTHON_INSTALL_DIR "${SR_CMAKE_VENV_DIRECTORY}/python")

    set(SR_PYTHON_URL "https://github.com/SpaRcle-Studio/Python")

    string(REPLACE "/" "\\" SR_PYTHON_INSTALL_DIR "${SR_PYTHON_INSTALL_DIR}")

    message(STATUS "InstallPython: Python URL: ${SR_PYTHON_URL}")
    message(STATUS "InstallPython: Python install dir: ${SR_PYTHON_INSTALL_DIR}")

    if (NOT EXISTS "${SR_PYTHON_INSTALL_DIR}")
        message(STATUS "InstallPythons: python not found, cloning...")

        execute_process(
            COMMAND git clone ${SR_PYTHON_URL} ${SR_PYTHON_INSTALL_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        )
    else()
        message(STATUS "InstallPython: python already exists, skipping clone.")
    endif()

    if (NOT EXISTS "${SR_PYTHON_INSTALL_DIR}/python.exe")
        message(FATAL_ERROR "InstallPython: failed to clone Python!")
    endif()

    set(SR_PYTHON_EXECUTABLE "${SR_PYTHON_INSTALL_DIR}/python.exe")
endif()

if (SR_PYTHON_EXECUTABLE)
    message(STATUS "InstallPython: Python executable: ${SR_PYTHON_EXECUTABLE}")
else()
    message(FATAL_ERROR "InstallPython: Python could not be installed!")
endif()

message(STATUS "InstallPython: installing Python packages...")
message(STATUS "InstallPython: Python packages: ${SR_PYTHON_REQUIREMENTS}")

execute_process(
    COMMAND "${SR_PYTHON_EXECUTABLE}" -m pip install ${SR_PYTHON_REQUIREMENTS}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
)

set(SR_PYTHON_PY_INSTALLER "${SR_PYTHON_EXECUTABLE} -m PyInstaller")
message(STATUS "InstallPython: PyInstaller: ${SR_PYTHON_PY_INSTALLER}")

if (NOT result EQUAL "0")
    message(FATAL_ERROR "InstallPython: failed to install Python packages! ${error_output}")
else()
    message(STATUS "InstallPython: python packages installed successfully.")
endif()

message(STATUS "InstallPython: checking python version...")
execute_process(COMMAND "${SR_PYTHON_EXECUTABLE}" --version)