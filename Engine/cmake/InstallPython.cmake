# Проверяем, установлен ли Python

set(SR_PYTHON_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/python")

if (UNIX)
    find_program(PYTHON_EXECUTABLE python)

    if (PYTHON_EXECUTABLE)
        message(STATUS "Python executable found: ${PYTHON_EXECUTABLE}")
    else()
        message(FATAL_ERROR "Python executable not found. Please install Python.")
    endif()

    set(SR_PYTHON_EXECUTABLE "${PYTHON_EXECUTABLE}")
elseif(EXISTS "${SR_PYTHON_INSTALL_DIR}/python.exe")
    set(SR_PYTHON_EXECUTABLE "${SR_PYTHON_INSTALL_DIR}/python.exe")
    message(STATUS "Python found: ${SR_PYTHON_EXECUTABLE}")
elseif (NOT SR_PYTHON_EXECUTABLE)
    message(STATUS "Python not found.")

    #set(SR_PYTHON_VERSION "3.13.0")
    #set(SR_PYTHON_ZIP "python-${SR_PYTHON_VERSION}-amd64.exe")
    #set(SR_PYTHON_URL "https://www.python.org/ftp/python/${SR_PYTHON_VERSION}/${SR_PYTHON_ZIP}")
    set(SR_PYTHON_URL "https://github.com/SpaRcle-Studio/Python")

    string(REPLACE "/" "\\" SR_PYTHON_INSTALL_DIR "${SR_PYTHON_INSTALL_DIR}")
    file(MAKE_DIRECTORY ${SR_PYTHON_INSTALL_DIR})

    #set(SR_PYTHON_INSTALLER "${CMAKE_CURRENT_BINARY_DIR}/python_installer.exe")

    #message(STATUS "Python version: ${SR_PYTHON_VERSION}")
    message(STATUS "Python URL: ${SR_PYTHON_URL}")
    message(STATUS "Python install dir: ${SR_PYTHON_INSTALL_DIR}")
    #message(STATUS "Python installer: ${SR_PYTHON_INSTALLER}")

    #if(NOT EXISTS ${SR_PYTHON_INSTALLER})
    #
    #    file(DOWNLOAD ${SR_PYTHON_URL} "${SR_PYTHON_INSTALLER}")
    #endif()

    message(STATUS "Clone python...")

    execute_process(
        COMMAND git clone ${SR_PYTHON_URL} ${SR_PYTHON_INSTALL_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    if (NOT EXISTS "${SR_PYTHON_INSTALL_DIR}/python.exe")
        message(FATAL_ERROR "Failed to clone Python!")
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

if (SR_PYTHON_EXECUTABLE)
    message(STATUS "Python executable: ${SR_PYTHON_EXECUTABLE}")
else()
    message(FATAL_ERROR "Python could not be installed!")
endif()

message(STATUS "Installing Python packages...")

execute_process(
    COMMAND "${SR_PYTHON_EXECUTABLE}" -m pip install clang libclang
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
)

if (NOT result EQUAL "0")
    message(FATAL_ERROR "Failed to install Python packages! ${error_output}")
endif ()
