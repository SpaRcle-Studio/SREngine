set(SR_CYGWIN_INSTALL_URL "https://www.cygwin.com/setup-x86_64.exe")
set(SR_CYGWIN_INSTALLER_PATH "${SR_VENV_DIR}/cygwin-installer.exe")
set(SR_CYGWIN_INSTALL_DIR "${SR_VENV_DIR}/cygwin")

if (NOT EXISTS ${SR_CYGWIN_INSTALLER_PATH})
    message(STATUS "CYGWIN installer not found, downloading...")

    file(DOWNLOAD
        ${SR_CYGWIN_INSTALL_URL}
        ${SR_CYGWIN_INSTALLER_PATH}
        SHOW_PROGRESS
        STATUS download_status
    )
endif()

if (NOT EXISTS ${SR_CYGWIN_INSTALLER_PATH})
    message(FATAL_ERROR "Failed to download CYGWIN installer. Status: ${download_status}")
endif()

message(STATUS "CYGWIN installer downloaded successfully to: ${SR_CYGWIN_INSTALLER_PATH}")

set(SR_CYGWIN_BASH "${SR_CYGWIN_INSTALL_DIR}/bin/bash.exe")

if (NOT EXISTS "${SR_CYGWIN_BASH}")
    message(STATUS "Installing CYGWIN, it may take few minutes...")

    execute_process(
        COMMAND ${SR_CYGWIN_INSTALLER_PATH}
        --no-admin
        --no-desktop
        --no-replaceonreboot
        --no-verify
        --no-version-check
        --no-shortcuts
        --no-startmenu
        --quiet-mode
        --only-site
        --root ${SR_CYGWIN_INSTALL_DIR}
        --site http://mirrors.kernel.org/sourceware/cygwin/
        --packages autoconf,automake,bison,gcc-core,gcc-g++,mingw64-i686-runtime,mingw64-i686-binutils,mingw64-i686-gcc-core,mingw64-i686-gcc-g++,mingw64-i686-pthreads,mingw64-i686-w32api,mingw64-x86_64-runtime,mingw64-x86_64-binutils,mingw64-x86_64-gcc-core,mingw64-x86_64-gcc-g++,mingw64-x86_64-pthreads,mingw64-x86_64-w32api,libtool,make,python,gettext-devel,gettext,intltool,libiconv,pkg-config,git,curl,wget,libxslt,bc,patch,cmake,perl,yasm,unzip
        RESULT_VARIABLE install_result
        OUTPUT_VARIABLE install_output
        ERROR_VARIABLE install_error
        COMMAND_ECHO STDOUT
    )

    if (NOT install_result EQUAL 0)
        message(FATAL_ERROR "Failed to install CYGWIN.\nError: ${install_error}\nOutput: ${install_output}")
    endif()
endif()

message(STATUS "CYGWIN installed successfully in: ${SR_CYGWIN_INSTALL_DIR}")

if (NOT EXISTS "${SR_CYGWIN_BASH}")
    message(FATAL_ERROR "CYGWIN Bash not found: ${SR_CYGWIN_BASH}")
endif()

