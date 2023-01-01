cmake_minimum_required(VERSION 3.0)

if (NOT CMAKE_VERSION VERSION_LESS 3.3)
    # Allow symbol visibility settings also on static libraries. CMake < 3.3
    # only sets the property on a shared library build.
    cmake_policy(SET CMP0063 NEW)

    # Support new IN_LIST if() operator.
    cmake_policy(SET CMP0057 NEW)
endif ()

include(CheckIncludeFile)
include(CMakeDependentOption)

# CMAKE_TOOLCHAIN_FILE must be set before `project' is called, which
# configures the base build environment and references the toolchain file
if (APPLE)
    if (DEFINED IOS_PLATFORM)
        if (NOT "${IOS_PLATFORM}" STREQUAL "OS"
                AND NOT "${IOS_PLATFORM}" STREQUAL "SIMULATOR"
                AND NOT "${IOS_PLATFORM}" STREQUAL "SIMULATOR64")
            message(FATAL_ERROR
                    "IOS_PLATFORM must be set to either OS, SIMULATOR, or SIMULATOR64")
        endif ()
        if (NOT "${CMAKE_GENERATOR}" STREQUAL "Xcode")
            message(AUTHOR_WARNING
                    "You should use Xcode generator with IOS_PLATFORM enabled to get Universal builds.")
        endif ()
        if (BUILD_SHARED_LIBS)
            message(FATAL_ERROR
                    "BUILD_SHARED_LIBS can not be on with IOS_PLATFORM enabled")
        endif ()
        if (BUILD_FRAMEWORK)
            message(FATAL_ERROR
                    "BUILD_FRAMEWORK can not be on with IOS_PLATFORM enabled")
        endif ()

        # iOS only uses static libraries
        set(BUILD_SHARED_LIBS OFF)

        set(CMAKE_TOOLCHAIN_FILE
                ${CMAKE_SOURCE_DIR}/libs/freetype/builds/cmake/iOS.cmake)
    endif ()
else ()
    if (DEFINED IOS_PLATFORM)
        message(FATAL_ERROR "IOS_PLATFORM is not supported on this platform")
    endif ()
endif ()


project(freetype C)

set(VERSION_MAJOR "2")
set(VERSION_MINOR "12")
set(VERSION_PATCH "1")

# Generate LIBRARY_VERSION and LIBRARY_SOVERSION.
set(LIBTOOL_REGEX "version_info='([0-9]+):([0-9]+):([0-9]+)'")
file(STRINGS "${PROJECT_SOURCE_DIR}/libs/freetype/builds/unix/configure.raw"
        VERSION_INFO
        REGEX ${LIBTOOL_REGEX})
string(REGEX REPLACE
        ${LIBTOOL_REGEX} "\\1"
        LIBTOOL_CURRENT "${VERSION_INFO}")
string(REGEX REPLACE
        ${LIBTOOL_REGEX} "\\2"
        LIBTOOL_REVISION "${VERSION_INFO}")
string(REGEX REPLACE
        ${LIBTOOL_REGEX} "\\3"
        LIBTOOL_AGE "${VERSION_INFO}")

# This is what libtool does internally on Unix platforms.
math(EXPR LIBRARY_SOVERSION "${LIBTOOL_CURRENT} - ${LIBTOOL_AGE}")
set(LIBRARY_VERSION "${LIBRARY_SOVERSION}.${LIBTOOL_AGE}.${LIBTOOL_REVISION}")

# External dependency library detection is automatic.  See the notes at the
# top of this file, for how to force or disable dependencies completely.
option(FT_DISABLE_ZLIB
        "Disable use of system zlib and use internal zlib library instead." OFF)
cmake_dependent_option(FT_REQUIRE_ZLIB
        "Require system zlib instead of internal zlib library." OFF
        "NOT FT_DISABLE_ZLIB" OFF)

option(FT_DISABLE_BZIP2
        "Disable support of bzip2 compressed fonts." OFF)
cmake_dependent_option(FT_REQUIRE_BZIP2
        "Require support of bzip2 compressed fonts." OFF
        "NOT FT_DISABLE_BZIP2" OFF)

option(FT_DISABLE_PNG
        "Disable support of PNG compressed OpenType embedded bitmaps." OFF)
cmake_dependent_option(FT_REQUIRE_PNG
        "Require support of PNG compressed OpenType embedded bitmaps." OFF
        "NOT FT_DISABLE_PNG" OFF)

option(FT_DISABLE_HARFBUZZ
        "Disable HarfBuzz (used for improving auto-hinting of OpenType fonts)." OFF)
cmake_dependent_option(FT_REQUIRE_HARFBUZZ
        "Require HarfBuzz for improving auto-hinting of OpenType fonts." OFF
        "NOT FT_DISABLE_HARFBUZZ" OFF)

option(FT_DISABLE_BROTLI
        "Disable support of compressed WOFF2 fonts." OFF)
cmake_dependent_option(FT_REQUIRE_BROTLI
        "Require support of compressed WOFF2 fonts." OFF
        "NOT FT_DISABLE_BROTLI" OFF)

option(FT_ENABLE_ERROR_STRINGS
        "Enable support for meaningful error descriptions." OFF)

# Disallow in-source builds
if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR
            "In-source builds are not permitted!  Make a separate folder for"
            " building, e.g.,\n"
            "  cmake -E make_directory build\n"
            "  cmake -E chdir build cmake ..\n"
            "Before that, remove the files created by this failed run with\n"
            "  cmake -E remove CMakeCache.txt\n"
            "  cmake -E remove_directory CMakeFiles")
endif ()


# Add local cmake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/libs/freetype/builds/cmake)


if (BUILD_FRAMEWORK)
    if (NOT "${CMAKE_GENERATOR}" STREQUAL "Xcode")
        message(FATAL_ERROR
                "You should use Xcode generator with BUILD_FRAMEWORK enabled")
    endif ()
    set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
    set(BUILD_SHARED_LIBS ON)
endif ()


# Find dependencies
include(FindPkgConfig)

if (NOT FT_DISABLE_HARFBUZZ)
    set(HARFBUZZ_MIN_VERSION "2.0.0")
    if (FT_REQUIRE_HARFBUZZ)
        find_package(HarfBuzz ${HARFBUZZ_MIN_VERSION} REQUIRED)
    else ()
        find_package(HarfBuzz ${HARFBUZZ_MIN_VERSION})
    endif ()
endif ()

if (NOT FT_DISABLE_PNG)
    if (FT_REQUIRE_PNG)
        find_package(PNG REQUIRED)
    else ()
        find_package(PNG)
    endif ()
endif ()

if (NOT FT_DISABLE_ZLIB)
    if (FT_REQUIRE_ZLIB)
        find_package(ZLIB REQUIRED)
    else ()
        find_package(ZLIB)
    endif ()
endif ()

if (NOT FT_DISABLE_BZIP2)
    # Genuine BZip2 does not provide bzip2.pc, but some platforms have it.
    # For better dependency in freetype2.pc, bzip2.pc is searched
    # regardless of the availability of libbz2. If bzip2.pc is found,
    # Requires.private is used instead of Libs.private.
    if (FT_REQUIRE_BZIP2)
        find_package(BZip2 REQUIRED)
    else ()
        find_package(BZip2)
    endif ()
    pkg_check_modules(PC_BZIP2 bzip2)
endif ()

if (NOT FT_DISABLE_BROTLI)
    if (FT_REQUIRE_BROTLI)
        find_package(BrotliDec REQUIRED PATHS /libs/freetype)
    else ()
        find_package(BrotliDec PATHS /libs/freetype)
    endif ()
endif ()

# Create the configuration file
if (UNIX)
    check_include_file("unistd.h" HAVE_UNISTD_H)
    check_include_file("fcntl.h" HAVE_FCNTL_H)

    file(READ "${PROJECT_SOURCE_DIR}/libs/freetype/builds/unix/ftconfig.h.in"
            FTCONFIG_H)
    if (HAVE_UNISTD_H)
        string(REGEX REPLACE
                "#undef +(HAVE_UNISTD_H)" "#define \\1 1"
                FTCONFIG_H "${FTCONFIG_H}")
    endif ()
    if (HAVE_FCNTL_H)
        string(REGEX REPLACE
                "#undef +(HAVE_FCNTL_H)" "#define \\1 1"
                FTCONFIG_H "${FTCONFIG_H}")
    endif ()
else ()
    file(READ "${PROJECT_SOURCE_DIR}/libs/freetype/include/freetype/config/ftconfig.h"
            FTCONFIG_H)
endif ()

set(FTCONFIG_H_NAME "${PROJECT_BINARY_DIR}/include/freetype/config/ftconfig.h")
if (EXISTS "${FTCONFIG_H_NAME}")
    file(READ "${FTCONFIG_H_NAME}" ORIGINAL_FTCONFIG_H)
else ()
    set(ORIGINAL_FTCONFIG_H "")
endif ()
if (NOT (ORIGINAL_FTCONFIG_H STREQUAL FTCONFIG_H))
    file(WRITE "${FTCONFIG_H_NAME}" "${FTCONFIG_H}")
endif ()


# Create the options file
file(READ "${PROJECT_SOURCE_DIR}/libs/freetype/include/freetype/config/ftoption.h"
        FTOPTION_H)
if (ZLIB_FOUND)
    string(REGEX REPLACE
            "/\\* +(#define +FT_CONFIG_OPTION_SYSTEM_ZLIB) +\\*/" "\\1"
            FTOPTION_H "${FTOPTION_H}")
endif ()
if (BZIP2_FOUND)
    string(REGEX REPLACE
            "/\\* +(#define +FT_CONFIG_OPTION_USE_BZIP2) +\\*/" "\\1"
            FTOPTION_H "${FTOPTION_H}")
endif ()
if (PNG_FOUND)
    string(REGEX REPLACE
            "/\\* +(#define +FT_CONFIG_OPTION_USE_PNG) +\\*/" "\\1"
            FTOPTION_H "${FTOPTION_H}")
endif ()
if (HARFBUZZ_FOUND)
    string(REGEX REPLACE
            "/\\* +(#define +FT_CONFIG_OPTION_USE_HARFBUZZ) +\\*/" "\\1"
            FTOPTION_H "${FTOPTION_H}")
endif ()
if (BROTLIDEC_FOUND)
    string(REGEX REPLACE
            "/\\* +(#define +FT_CONFIG_OPTION_USE_BROTLI) +\\*/" "\\1"
            FTOPTION_H "${FTOPTION_H}")
endif ()

if (FT_ENABLE_ERROR_STRINGS)
    string(REGEX REPLACE
            "/\\* +(#define +FT_CONFIG_OPTION_ERROR_STRINGS) +\\*/" "\\1"
            FTOPTION_H "${FTOPTION_H}")
endif ()

set(FTOPTION_H_NAME "${PROJECT_BINARY_DIR}/include/freetype/config/ftoption.h")
if (EXISTS "${FTOPTION_H_NAME}")
    file(READ "${FTOPTION_H_NAME}" ORIGINAL_FTOPTION_H)
else ()
    set(ORIGINAL_FTOPTION_H "")
endif ()
if (NOT (ORIGINAL_FTOPTION_H STREQUAL FTOPTION_H))
    file(WRITE "${FTOPTION_H_NAME}" "${FTOPTION_H}")
endif ()


file(GLOB PUBLIC_HEADERS "libs/freetype/include/ft2build.h" "libs/freetype/include/freetype/*.h")
file(GLOB PUBLIC_CONFIG_HEADERS "libs/freetype/include/freetype/config/*.h")
file(GLOB PRIVATE_HEADERS "libs/freetype/include/freetype/internal/*.h")

set(BASE_SRCS
        libs/freetype/src/autofit/autofit.c
        libs/freetype/src/base/ftbase.c
        libs/freetype/src/base/ftbbox.c
        libs/freetype/src/base/ftbdf.c
        libs/freetype/src/base/ftbitmap.c
        libs/freetype/src/base/ftcid.c
        libs/freetype/src/base/ftfstype.c
        libs/freetype/src/base/ftgasp.c
        libs/freetype/src/base/ftglyph.c
        libs/freetype/src/base/ftgxval.c
        libs/freetype/src/base/ftinit.c
        libs/freetype/src/base/ftmm.c
        libs/freetype/src/base/ftotval.c
        libs/freetype/src/base/ftpatent.c
        libs/freetype/src/base/ftpfr.c
        libs/freetype/src/base/ftstroke.c
        libs/freetype/src/base/ftsynth.c
        libs/freetype/src/base/fttype1.c
        libs/freetype/src/base/ftwinfnt.c
        libs/freetype/src/bdf/bdf.c
        libs/freetype/src/bzip2/ftbzip2.c
        libs/freetype/src/cache/ftcache.c
        libs/freetype/src/cff/cff.c
        libs/freetype/src/cid/type1cid.c
        libs/freetype/src/gzip/ftgzip.c
        libs/freetype/src/lzw/ftlzw.c
        libs/freetype/src/pcf/pcf.c
        libs/freetype/src/pfr/pfr.c
        libs/freetype/src/psaux/psaux.c
        libs/freetype/src/pshinter/pshinter.c
        libs/freetype/src/psnames/psnames.c
        libs/freetype/src/raster/raster.c
        libs/freetype/src/sdf/sdf.c
        libs/freetype/src/sfnt/sfnt.c
        libs/freetype/src/smooth/smooth.c
        libs/freetype/src/svg/svg.c
        libs/freetype/src/truetype/truetype.c
        libs/freetype/src/type1/type1.c
        libs/freetype/src/type42/type42.c
        libs/freetype/src/winfonts/winfnt.c
        )

if (UNIX)
    if (ANDROID_NDK)
        list(APPEND BASE_SRCS "libs/freetype/src/base/ftsystem.c")
    else()
        list(APPEND BASE_SRCS "libs/freetype/builds/unix/ftsystem.c")
    endif()
elseif (WIN32)
    list(APPEND BASE_SRCS "libs/freetype/builds/windows/ftsystem.c")
else ()
    list(APPEND BASE_SRCS "libs/freetype/src/base/ftsystem.c")
endif ()

if (WIN32)
    enable_language(RC)
    list(APPEND BASE_SRCS libs/freetype/builds/windows/ftdebug.c
            libs/freetype/src/base/ftver.rc)
elseif (WINCE)
    list(APPEND BASE_SRCS libs/freetype/builds/wince/ftdebug.c)
else ()
    list(APPEND BASE_SRCS libs/freetype/src/base/ftdebug.c)
endif ()

if (BUILD_FRAMEWORK)
    list(APPEND BASE_SRCS libs/freetype/builds/mac/freetype-Info.plist)
endif ()


if (NOT DISABLE_FORCE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX d)
endif ()

add_library(freetype
        ${PUBLIC_HEADERS}
        ${PUBLIC_CONFIG_HEADERS}
        ${PRIVATE_HEADERS}
        ${BASE_SRCS}
        )

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(freetype PRIVATE -Wno-unused-function -Wimplicit-function-declaration)
endif()

set_target_properties(
        freetype PROPERTIES
        C_VISIBILITY_PRESET hidden)

target_compile_definitions(
        freetype PRIVATE FT2_BUILD_LIBRARY)

if (WIN32)
    target_compile_definitions(
            freetype PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
    if (BUILD_SHARED_LIBS)
        target_compile_definitions(
                freetype PRIVATE DLL_EXPORT)
    endif ()
endif ()

if (BUILD_SHARED_LIBS)
    set_target_properties(freetype PROPERTIES
            VERSION ${LIBRARY_VERSION}
            SOVERSION ${LIBRARY_SOVERSION})
endif ()

# Pick up ftconfig.h and ftoption.h generated above, first.
target_include_directories(
        freetype
        PUBLIC
        $<INSTALL_INTERFACE:include/freetype2>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/libs/freetype/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype/include>
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/libs/freetype/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype/include

        # Make <ftconfig.h> available for builds/unix/ftsystem.c.
        ${CMAKE_CURRENT_BINARY_DIR}/libs/freetype/include/freetype/config
)


if (BUILD_FRAMEWORK)
    set_property(SOURCE ${PUBLIC_CONFIG_HEADERS}
            PROPERTY MACOSX_PACKAGE_LOCATION Headers/config
            )
    set_target_properties(freetype PROPERTIES
            FRAMEWORK TRUE
            MACOSX_FRAMEWORK_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype/builds/mac/freetype-Info.plist
            PUBLIC_HEADER "${PUBLIC_HEADERS}"
            XCODE_ATTRIBUTE_INSTALL_PATH "@rpath"
            )
endif ()

# 'freetype-interface' is an interface library, to be accessed with
# `EXPORT_NAME Freetype::Freetype`.  This is the target name provided by
# CMake's `FindFreetype.cmake`, so we provide it for compatibility.
add_library(freetype-interface INTERFACE)
set_target_properties(freetype-interface PROPERTIES
        EXPORT_NAME Freetype::Freetype
        INTERFACE_LINK_LIBRARIES freetype)

set(PKGCONFIG_REQUIRES "")
set(PKGCONFIG_REQUIRES_PRIVATE "")
set(PKGCONFIG_LIBS "-L\${libdir} -lfreetype")
set(PKGCONFIG_LIBS_PRIVATE "")

if (ZLIB_FOUND)
    target_link_libraries(freetype PRIVATE ${ZLIB_LIBRARIES})
    target_include_directories(freetype PRIVATE ${ZLIB_INCLUDE_DIRS})
    list(APPEND PKGCONFIG_REQUIRES_PRIVATE "zlib")
endif ()
if (BZIP2_FOUND)
    target_link_libraries(freetype PRIVATE ${BZIP2_LIBRARIES})
    target_include_directories(freetype PRIVATE ${BZIP2_INCLUDE_DIR}) # not BZIP2_INCLUDE_DIRS
    if (PC_BZIP2_FOUND)
        list(APPEND PKGCONFIG_REQUIRES_PRIVATE "bzip2")
    else ()
        list(APPEND PKGCONFIG_LIBS_PRIVATE "-lbz2")
    endif ()
endif ()
if (PNG_FOUND)
    target_link_libraries(freetype PRIVATE ${PNG_LIBRARIES})
    target_compile_definitions(freetype PRIVATE ${PNG_DEFINITIONS})
    target_include_directories(freetype PRIVATE ${PNG_INCLUDE_DIRS})
    list(APPEND PKGCONFIG_REQUIRES_PRIVATE "libpng")
endif ()
if (HarfBuzz_FOUND)
    target_link_libraries(freetype PRIVATE ${HarfBuzz_LIBRARY})
    target_include_directories(freetype PRIVATE ${HarfBuzz_INCLUDE_DIRS})
    list(APPEND PKGCONFIG_REQUIRES_PRIVATE "harfbuzz >= ${HARFBUZZ_MIN_VERSION}")
endif ()
if (BROTLIDEC_FOUND)
    target_link_libraries(freetype PRIVATE ${BROTLIDEC_LIBRARIES})
    target_compile_definitions(freetype PRIVATE ${BROTLIDEC_DEFINITIONS})
    target_include_directories(freetype PRIVATE ${BROTLIDEC_INCLUDE_DIRS})
    list(APPEND PKGCONFIG_REQUIRES_PRIVATE "libbrotlidec")
endif ()


# Installation
include(GNUInstallDirs)

if (NOT SKIP_INSTALL_HEADERS AND NOT SKIP_INSTALL_ALL)
    install(
            # Note the trailing slash in the argument to `DIRECTORY'!
            DIRECTORY ${PROJECT_SOURCE_DIR}/libs/freetype/include/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/freetype2
            COMPONENT headers
            PATTERN "internal" EXCLUDE
            PATTERN "ftconfig.h" EXCLUDE
            PATTERN "ftoption.h" EXCLUDE)
    install(
            FILES ${PROJECT_BINARY_DIR}/include/freetype/config/ftconfig.h
            ${PROJECT_BINARY_DIR}/include/freetype/config/ftoption.h
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/freetype2/freetype/config
            COMPONENT headers)
endif ()

if (NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL)
    # Generate the pkg-config file
    file(READ "${PROJECT_SOURCE_DIR}/libs/freetype/builds/unix/freetype2.in" FREETYPE2_PC_IN)

    string(REPLACE ";" ", " PKGCONFIG_REQUIRES_PRIVATE "${PKGCONFIG_REQUIRES_PRIVATE}")

    string(REPLACE "%prefix%" ${CMAKE_INSTALL_PREFIX}
            FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
    string(REPLACE "%exec_prefix%" "\${prefix}"
            FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
    string(REPLACE "%libdir%" "\${prefix}/${CMAKE_INSTALL_LIBDIR}"
            FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
    string(REPLACE "%includedir%" "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}"
            FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
    string(REPLACE "%ft_version%" "${LIBTOOL_CURRENT}.${LIBTOOL_REVISION}.${LIBTOOL_AGE}"
            FREETYPE2_PC_IN ${FREETYPE2_PC_IN})

    if (BUILD_SHARED_LIBS)
        string(REPLACE "%PKGCONFIG_REQUIRES%" "${PKGCONFIG_REQUIRES}"
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
        string(REPLACE "%PKGCONFIG_REQUIRES_PRIVATE%" "${PKGCONFIG_REQUIRES_PRIVATE}"
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
        string(REPLACE "%PKGCONFIG_LIBS%" "${PKGCONFIG_LIBS}"
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
        string(REPLACE "%PKGCONFIG_LIBS_PRIVATE%" "${PKGCONFIG_LIBS_PRIVATE}"
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
    else ()
        string(REPLACE "%PKGCONFIG_REQUIRES%" "${PKGCONFIG_REQUIRES} ${PKGCONFIG_REQUIRES_PRIVATE}"
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
        string(REPLACE "%PKGCONFIG_REQUIRES_PRIVATE%" ""
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
        string(REPLACE "%PKGCONFIG_LIBS%" "${PKGCONFIG_LIBS} ${PKGCONFIG_LIBS_PRIVATE}"
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
        string(REPLACE "%PKGCONFIG_LIBS_PRIVATE%" ""
                FREETYPE2_PC_IN ${FREETYPE2_PC_IN})
    endif ()

    set(FREETYPE2_PC_IN_NAME "${PROJECT_BINARY_DIR}/freetype2.pc")
    if (EXISTS "${FREETYPE2_PC_IN_NAME}")
        file(READ "${FREETYPE2_PC_IN_NAME}" ORIGINAL_FREETYPE2_PC_IN)
    else ()
        set(ORIGINAL_FREETYPE2_PC_IN "")
    endif ()
    if (NOT (ORIGINAL_FREETYPE2_PC_IN STREQUAL FREETYPE2_PC_IN))
        file(WRITE "${FREETYPE2_PC_IN_NAME}" ${FREETYPE2_PC_IN})
    endif ()

    install(
            FILES ${PROJECT_BINARY_DIR}/freetype2.pc
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
            COMPONENT pkgconfig)

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${PROJECT_BINARY_DIR}/freetype-config-version.cmake
            VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
            COMPATIBILITY SameMajorVersion)

    install(
            TARGETS freetype freetype-interface
            EXPORT freetype-targets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            FRAMEWORK DESTINATION Library/Frameworks
            COMPONENT libraries)
    install(
            EXPORT freetype-targets
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/freetype
            FILE freetype-config.cmake
            COMPONENT headers)
    install(
            FILES ${PROJECT_BINARY_DIR}/freetype-config-version.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/freetype
            COMPONENT headers)
endif ()


# Packaging
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The FreeType font rendering library.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.TXT")

set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

if (WIN32)
    set(CPACK_GENERATOR ZIP)
else ()
    set(CPACK_GENERATOR TGZ)
endif ()

set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C/C++ Headers")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
        "Library used to build programs which use FreeType")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
        "C/C++ header files for use with FreeType")
set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)
set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set(CPACK_COMPONENT_HEADERS_GROUP "Development")

