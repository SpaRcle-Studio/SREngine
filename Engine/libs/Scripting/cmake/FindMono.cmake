# Find the xbuild tool and mono interpreter
#
# Mono_FOUND             System has Mono dev files, as well as mono, mcs, gmcs and gacutil if not Mono_ONLY_LIBRARIES_REQUIRED
# Mono_EXECUTABLE        Where to find 'mono'
# XBUILD_EXECUTABLE      Where to find 'xbuild'
# Mono_VERSION           The version number of the Mono interpreter
# Mono_LIBRARY           Path to the Mono library
# Mono_INCLUDE_DIR       Path to the Mono include directory

set(Mono_ROOT "" CACHE PATH "Set the location of the Mono root directory")

# Поиск сначала в локальной сборке, затем в Mono_ROOT, затем стандартные пути
find_program(Mono_EXECUTABLE mono
    "${Mono_ROOT}/bin"
    PATH_SUFFIXES bin
)

find_program(XBUILD_EXECUTABLE xbuild
    "${Mono_ROOT}/bin"
    PATH_SUFFIXES bin
)

find_path(Mono_INCLUDE_DIR mono-2.0/mono/jit/jit.h
    "${Mono_ROOT}/include"
    PATH_SUFFIXES mono-2.0
)

find_library(Mono_LIBRARY NAMES mono-2.0-sgen
    "${Mono_ROOT}/lib"
)

# Если не найдено, ищем в стандартных местах
if(NOT Mono_EXECUTABLE OR NOT XBUILD_EXECUTABLE OR NOT Mono_INCLUDE_DIR OR NOT Mono_LIBRARY)
    if(WIN32)
        set(csharp_Mono_bin_hints
                "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Novell\\Mono;DefaultCLR]/bin"
                "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Novell\\Mono\\${Mono_CLR};SdkInstallRoot]/bin"
        )
    elseif(APPLE)
        set(csharp_Mono_bin_hints
                "/Library/Frameworks/Mono.framework/Commands"
                "/usr"
                "/usr/local"
                "/usr/lib/mono/2.0"
                "/opt/novell/mono"
        )
    else()
        set(csharp_Mono_bin_hints
                "/usr/bin/"
                "/usr/local/bin/"
                "/usr/lib/mono/2.0"
                "/opt/novell/mono/bin"
        )
    endif()

    find_program(Mono_EXECUTABLE mono
            HINTS ${csharp_Mono_bin_hints}
            PATH_SUFFIXES bin
    )

    find_program(XBUILD_EXECUTABLE xbuild
            HINTS ${csharp_Mono_bin_hints}
            PATH_SUFFIXES bin
    )
endif()

# Получение версии Mono
if(Mono_EXECUTABLE)
    execute_process(
            COMMAND ${Mono_EXECUTABLE} -V
            OUTPUT_VARIABLE csharp_Mono_version_string
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    string(REGEX MATCH "([0-9]+\\.[0-9]+\\.[0-9]+)" Mono_VERSION "${csharp_Mono_version_string}")
endif()

# Проверка найденных файлов
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Mono DEFAULT_MSG Mono_EXECUTABLE XBUILD_EXECUTABLE Mono_INCLUDE_DIR Mono_LIBRARY)

# Пометка переменных как `ADVANCED`
mark_as_advanced(Mono_EXECUTABLE XBUILD_EXECUTABLE Mono_INCLUDE_DIR Mono_LIBRARY Mono_VERSION)