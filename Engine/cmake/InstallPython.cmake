# We need to ensure that Python is installed as well as the required packages.

set(SR_VENV_DIR "${PROJECT_SOURCE_DIR}/../.venv")

if (UNIX AND NOT ANDROID_NDK)
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

    message(STATUS "InstallPython: installing clang and libclang...")

    execute_process(
        COMMAND ${SR_PYTHON_EXECUTABLE} -m pip install clang==17.0.6 libclang==18.1.1
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output
    )
elseif (NOT SR_PYTHON_EXECUTABLE)
    message(STATUS "InstallPython: Python not found.")

    set(SR_PYTHON_INSTALL_DIR "${SR_CMAKE_VENV_DIRECTORY}/python")

    #set(SR_PYTHON_VERSION "3.13.0")
    #set(SR_PYTHON_ZIP "python-${SR_PYTHON_VERSION}-amd64.exe")
    #set(SR_PYTHON_URL "https://www.python.org/ftp/python/${SR_PYTHON_VERSION}/${SR_PYTHON_ZIP}")
    set(SR_PYTHON_URL "https://github.com/SpaRcle-Studio/Python")

    string(REPLACE "/" "\\" SR_PYTHON_INSTALL_DIR "${SR_PYTHON_INSTALL_DIR}")

    #set(SR_PYTHON_INSTALLER "${CMAKE_CURRENT_BINARY_DIR}/python_installer.exe")

    #message(STATUS "Python version: ${SR_PYTHON_VERSION}")
    message(STATUS "InstallPython: Python URL: ${SR_PYTHON_URL}")
    message(STATUS "InstallPython: Python install dir: ${SR_PYTHON_INSTALL_DIR}")
    #message(STATUS "Python installer: ${SR_PYTHON_INSTALLER}")

    #if(NOT EXISTS ${SR_PYTHON_INSTALLER})
    #
    #    file(DOWNLOAD ${SR_PYTHON_URL} "${SR_PYTHON_INSTALLER}")
    #endif()

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

    # Проверяем, успешно ли скачан установщик
    #if(NOT EXISTS ${SR_PYTHON_INSTALLER})
    #    message(FATAL_ERROR "Failed to download Python installer!")
    #endif()

#    message(STATUS "Repairing repository Python...")
#
#    # Восстанавливаем установку Python
#    execute_process(
#        COMMAND "${SR_PYTHON_INSTALLER}" InstallAllUsers=0 /repair /quiet /log "Python-Uninstall.log"
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    )
#
#    message(STATUS "Uninstalling repository Python... (don’t worry)")
#
#    # Удаляем старую версию Python
#    execute_process(
#        COMMAND "${SR_PYTHON_INSTALLER}"  InstallAllUsers=0 /uninstall /quiet /log "Python-Uninstall.log"
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    )
#
#    message(STATUS "Installing repository Python...")
#
#    # Устанавливаем Python
#    execute_process(
#        COMMAND "${SR_PYTHON_INSTALLER}" TargetDir=${SR_PYTHON_INSTALL_DIR} /quiet /log "Python-Install.log"
#            Include_test=0 Include_doc=0 Include_dev=0 Include_exe=1 Include_launcher=0 Include_pip=1 Include_tcltk=0 InstallAllUsers=0
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        RESULT_VARIABLE INSTALL_RESULT
#    )
#
#    if (NOT INSTALL_RESULT EQUAL "0")
#        message(FATAL_ERROR "Failed to install Python! See \"Python-Install.log\" for details.")
#    endif()
#
#    set(SR_PYTHON_EXECUTABLE "${SR_PYTHON_INSTALL_DIR}/python.exe")
#
#    if(NOT EXISTS "${SR_PYTHON_INSTALL_DIR}/python.exe")
#        set(SR_PYTHON_EXECUTABLE "${SR_PYTHON_INSTALL_DIR}/python.exe")
#        message(FATAL_ERROR "Failed to install Python!")
#    endif ()
endif()

if (NOT UNIX OR ANDROID_NDK)
    if (SR_PYTHON_EXECUTABLE)
        message(STATUS "InstallPython: Python executable: ${SR_PYTHON_EXECUTABLE}")
    else()
        message(FATAL_ERROR "InstallPython: Python could not be installed!")
    endif()

    message(STATUS "InstallPython: installing Python packages...")

    execute_process(
        COMMAND "${SR_PYTHON_EXECUTABLE}" -m pip install clang==17.0.6 libclang==18.1.1 pyinstaller==6.13.0
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
endif()

message(STATUS "InstallPython: checking python version...")
execute_process(COMMAND "${SR_PYTHON_EXECUTABLE}" --version)