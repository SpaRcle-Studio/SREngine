set(SR_MSYS2_INSTALL_URL "https://github.com/msys2/msys2-installer/releases/download/2025-02-21/msys2-x86_64-20250221.exe")
set(SR_MSYS2_INSTALLER_PATH "${CMAKE_CURRENT_BINARY_DIR}/msys2-installer.exe")
set(SR_MSYS2_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/msys2")

if (NOT EXISTS ${SR_MSYS2_INSTALLER_PATH})
    message(STATUS "MSYS2 installer not found, downloading...")

    file(DOWNLOAD
        ${SR_MSYS2_INSTALL_URL}
        ${SR_MSYS2_INSTALLER_PATH}
        SHOW_PROGRESS
        STATUS download_status
    )
endif()

if (NOT EXISTS ${SR_MSYS2_INSTALLER_PATH})
    message(FATAL_ERROR "Failed to download MSYS2 installer. Status: ${download_status}")
endif()

message(STATUS "MSYS2 installer downloaded successfully to: ${SR_MSYS2_INSTALLER_PATH}")

if (NOT EXISTS "${SR_MSYS2_INSTALL_DIR}/usr/bin/bash.exe")
    message(STATUS "Installing MSYS2...")

    execute_process(
        COMMAND ${SR_MSYS2_INSTALLER_PATH} install --root ${SR_MSYS2_INSTALL_DIR} --confirm-command
        RESULT_VARIABLE install_result
    )

    if (NOT install_result EQUAL 0)
        message(FATAL_ERROR "Failed to install MSYS2.")
    endif()
endif()

message(STATUS "MSYS2 installed successfully in: ${SR_MSYS2_INSTALL_DIR}")

# Инициализация MSYS2 и обновление пакетов
set(SR_MSYS2_BASH "${SR_MSYS2_INSTALL_DIR}/usr/bin/bash.exe")
set(SR_MSYS2_PACMAN "${SR_MSYS2_INSTALL_DIR}/usr/bin/pacman.exe")

# Проверяем, существует ли MSYS2 bash
if (NOT EXISTS "${SR_MSYS2_BASH}")
    message(FATAL_ERROR "MSYS2 Bash not found: ${SR_MSYS2_BASH}")
endif()

# Выводим версию pacman для диагностики
execute_process(
    COMMAND ${SR_MSYS2_BASH} -lc "pacman --version"
    RESULT_VARIABLE pacman_version_result
    OUTPUT_VARIABLE pacman_version_output
    ERROR_VARIABLE pacman_version_error
)

message(STATUS "Pacman Version Output: ${pacman_version_output}")
message(STATUS "Pacman Version Error: ${pacman_version_error}")

message(STATUS "Synchronizing MSYS2 package database...")

execute_process(
    COMMAND ${SR_MSYS2_BASH} -lc "pacman -Sy --noconfirm"
    RESULT_VARIABLE pacman_sy_result
    OUTPUT_VARIABLE pacman_sy_output
    ERROR_VARIABLE pacman_sy_error
)

if (NOT pacman_sy_result EQUAL 0)
    message(FATAL_ERROR "Failed to synchronize MSYS2 package database.\nOutput: ${pacman_sy_output}\nError: ${pacman_sy_error}")
endif()

# Удаляем конфликтующий пакет перед установкой
#message(STATUS "Removing conflicting pkg-config package...")
#execute_process(
#    COMMAND ${SR_MSYS2_BASH} -lc "pacman -R --noconfirm mingw-w64-x86_64-pkg-config"
#    RESULT_VARIABLE remove_pkgconfig_result
#    OUTPUT_VARIABLE remove_pkgconfig_output
#    ERROR_VARIABLE remove_pkgconfig_error
#)

# Устанавливаем необходимые инструменты

# Базовые пакеты
set(SR_MSYS2_PACKAGES
    "autoconf automake libtool make gcc cmake ninja git python curl wget libxslt bc patch perl yasm unzip"
)

# MinGW 64-bit пакеты
set(SR_MSYS2_MINGW_PACKAGES
    #"mingw-w64-x86_64-toolchain mingw-w64-x86_64-make mingw-w64-x86_64-libtool mingw-w64-x86_64-binutils mingw-w64-x86_64-gcc mingw-w64-x86_64-gcc-libs mingw-w64-x86_64-pthreads mingw-w64-x86_64-winpthreads mingw-w64-x86_64-windows-default-manifest mingw-w64-x86_64-pkgconf"
    "mingw-w64-x86_64-toolchain mingw-w64-x86_64-make mingw-w64-x86_64-libtool mingw-w64-x86_64-binutils mingw-w64-x86_64-gcc mingw-w64-x86_64-gcc-libs mingw-w64-x86_64-windows-default-manifest mingw-w64-x86_64-pkgconf"
)

# MinGW 64-bit пакеты
#set(SR_MSYS2_MINGW_PACKAGES
#    "mingw-w64-x86_64-toolchain mingw-w64-x86_64-make mingw-w64-x86_64-libtool"
#)

message(STATUS "Installing MSYS2 packages: ${SR_MSYS2_PACKAGES}")
message(STATUS "Installing MSYS2 MinGW packages: ${SR_MSYS2_MINGW_PACKAGES}")

execute_process(
    COMMAND ${SR_MSYS2_BASH} -lc "export LANG=C && pacman -S --needed --noconfirm ${SR_MSYS2_PACKAGES} ${SR_MSYS2_MINGW_PACKAGES}"
    RESULT_VARIABLE pacman_install_result
    OUTPUT_VARIABLE pacman_install_output
    ERROR_VARIABLE pacman_install_error
)

if (NOT pacman_install_result EQUAL 0)
    message(FATAL_ERROR "Failed to install required MSYS2 packages.\nOutput: ${pacman_install_output}\nError: ${pacman_install_error}")
endif()

message(STATUS "MSYS2 is ready with all required packages installed.")
