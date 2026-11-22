# Created by OpenAI Codex on 22.11.2026.

set(SR_BUILD_TEXTURE_TOOLS OFF CACHE INTERNAL "" FORCE)
if(NOT ANDROID AND NOT EMSCRIPTEN)
    set(SR_BUILD_TEXTURE_TOOLS ON CACHE INTERNAL "" FORCE)
endif()

if(NOT SR_BUILD_TEXTURE_TOOLS)
    return()
endif()

set(SR_TEXTURE_VENDOR_DIR "${CORE_ROOT_DIR}/libs/Graphics/libs")
set(SR_TEXTURE_PREVIOUS_SHARED_LIBS "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS OFF)
foreach(SR_TEXTURE_DEPENDENCY IN ITEMS KTX-Software etc2comp)
    if(NOT EXISTS "${SR_TEXTURE_VENDOR_DIR}/${SR_TEXTURE_DEPENDENCY}/CMakeLists.txt")
        message(FATAL_ERROR "[SpaRcle Engine] Missing texture encoder source: ${SR_TEXTURE_VENDOR_DIR}/${SR_TEXTURE_DEPENDENCY}. Add the dependency checkout before enabling SR_BUILD_TEXTURE_TOOLS.")
    endif()
endforeach()

set(KTX_FEATURE_TOOLS OFF)
set(KTX_FEATURE_TESTS OFF)
set(KTX_FEATURE_DOC OFF)
set(KTX_FEATURE_JS OFF)
set(KTX_FEATURE_JNI OFF)
set(KTX_FEATURE_PY OFF)
set(KTX_FEATURE_LOADTEST_APPS OFF)
set(LIBKTX_FEATURE_ETC_UNPACK OFF)
set(LIBKTX_FEATURE_GL_UPLOAD OFF)
set(LIBKTX_FEATURE_VK_UPLOAD OFF)
set(LIBKTX_VERSION_FULL ON)
set(LIBKTX_VERSION_READ_ONLY OFF)
# Use KTX's pinned astcenc to avoid duplicate encoder symbols.
set(ASTCENC_CLI OFF)
set(ASTCENC_UNITTEST OFF)
set(ASTCENC_WERROR OFF)
foreach(SR_ASTC_ISA IN ITEMS NATIVE AVX512 AVX2 SSE41 SSE2 NEON SVE_128 SVE_256)
    set(ASTCENC_ISA_${SR_ASTC_ISA} OFF)
endforeach()
set(ASTCENC_ISA_NONE ON)
set(SR_TEXTURE_ASTC_TARGET astcenc-none-static)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SR_TEXTURE_PROCESSOR)
if(WIN32 AND CMAKE_CXX_COMPILER_ARCHITECTURE_ID)
    string(TOLOWER "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" SR_TEXTURE_PROCESSOR)
endif()
if(NOT APPLE AND CMAKE_SIZEOF_VOID_P EQUAL 8
    AND (SR_TEXTURE_PROCESSOR MATCHES "^(amd64|x86_64|x64)$" OR CMAKE_GENERATOR_PLATFORM STREQUAL "x64")
    AND NOT CMAKE_GENERATOR_PLATFORM MATCHES "^[Aa][Rr][Mm]64"
    AND NOT CMAKE_VS_PLATFORM_NAME MATCHES "^[Aa][Rr][Mm]64")
    set(ASTCENC_ISA_NONE OFF)
    set(ASTCENC_ISA_SSE2 ON)
    set(SR_TEXTURE_ASTC_TARGET astcenc-sse2-static)
endif()
set(BASISU_SSE OFF)
set(LIBKTX_FEATURE_BASISU_SSE OFF)
function(sr_add_optimized_texture_dependency SR_SOURCE SR_BINARY)
    # Optimize codecs in Debug too, while retaining the editor's CRT and debug symbols.
    if(MSVC)
        string(REGEX REPLACE "/RTC[1su]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REPLACE "/Od" "/O2" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REPLACE "/Ob0" "/Ob2" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    endif()
    add_subdirectory("${SR_SOURCE}" "${SR_BINARY}")
    foreach(SR_CODEC_TARGET IN LISTS ARGN)
        if(MSVC)
            target_compile_options(${SR_CODEC_TARGET} PRIVATE "$<$<CONFIG:Debug>:/O2>")
        else()
            target_compile_options(${SR_CODEC_TARGET} PRIVATE "$<$<CONFIG:Debug>:-O2>")
        endif()
    endforeach()
endfunction()
set(SR_TEXTURE_PREVIOUS_PIC "${CMAKE_POSITION_INDEPENDENT_CODE}")
set(SR_TEXTURE_PREVIOUS_PIC_DEFINED OFF)
if(DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
    set(SR_TEXTURE_PREVIOUS_PIC_DEFINED ON)
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
sr_add_optimized_texture_dependency("${SR_TEXTURE_VENDOR_DIR}/KTX-Software"
    "${CMAKE_CURRENT_BINARY_DIR}/TextureTools/KTX" ${SR_TEXTURE_ASTC_TARGET})
if(TARGET libzstd_static)
    # cpptrace and KTX must use one Zstd implementation in static engine builds.
    get_target_property(SR_BASISU_SOURCES basisu_encoder SOURCES)
    list(FILTER SR_BASISU_SOURCES EXCLUDE REGEX "(^|/)zstd/zstd\\.c$")
    set_property(TARGET basisu_encoder PROPERTY SOURCES "${SR_BASISU_SOURCES}")
    target_link_libraries(basisu_encoder PRIVATE libzstd_static)
    target_link_libraries(ktx PRIVATE libzstd_static)
    set_target_properties(libzstd_static PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
if(SR_TEXTURE_PREVIOUS_PIC_DEFINED)
    set(CMAKE_POSITION_INDEPENDENT_CODE "${SR_TEXTURE_PREVIOUS_PIC}")
else()
    unset(CMAKE_POSITION_INDEPENDENT_CODE)
endif()
sr_add_optimized_texture_dependency("${SR_TEXTURE_VENDOR_DIR}/etc2comp/EtcLib"
    "${CMAKE_CURRENT_BINARY_DIR}/TextureTools/ETC" EtcLib)
option(SR_TEXTURE_USE_ETCPAK "Use etcpak for fast ETC2/EAC texture export" ON)
if(SR_TEXTURE_USE_ETCPAK)
    set(SR_ETCPAK_DIR "${SR_TEXTURE_VENDOR_DIR}/etcpak")
    foreach(SR_ETCPAK_SOURCE IN ITEMS ProcessRGB.cpp Dither.cpp Tables.cpp ProcessRGB.hpp)
        if(NOT EXISTS "${SR_ETCPAK_DIR}/${SR_ETCPAK_SOURCE}")
            message(FATAL_ERROR "[SpaRcle Engine] Missing etcpak source: ${SR_ETCPAK_DIR}/${SR_ETCPAK_SOURCE}. Add https://github.com/wolfpld/etcpak here, or disable SR_TEXTURE_USE_ETCPAK.")
        endif()
    endforeach()
    # Build only the codec; upstream CMake builds a CLI and fetches Tracy/libpng.
    function(sr_add_texture_etcpak)
        if(MSVC)
            string(REGEX REPLACE "/RTC[1su]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
            string(REPLACE "/Od" "/O2" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
            string(REPLACE "/Ob0" "/Ob2" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        endif()
        # A child directory retains these flags during generation after this function returns.
        add_subdirectory("${CORE_ROOT_DIR}/cmake/etcpak"
            "${CMAKE_CURRENT_BINARY_DIR}/TextureTools/Etcpak")
    endfunction()
    sr_add_texture_etcpak()
    target_include_directories(Engine PRIVATE "${SR_ETCPAK_DIR}")
    target_link_libraries(Engine PRIVATE SRTextureEtcpak)
    target_compile_definitions(Engine PRIVATE SR_TEXTURE_ETCPAK)
endif()
sr_add_optimized_texture_dependency("${SR_TEXTURE_VENDOR_DIR}/cmp_core"
    "${CMAKE_CURRENT_BINARY_DIR}/TextureTools/BC" CMP_Core)

target_compile_definitions(Engine PRIVATE SR_BUILD_TEXTURE_TOOLS KHRONOS_STATIC)
target_include_directories(Engine PRIVATE
    "${SR_TEXTURE_VENDOR_DIR}/cmp_core/source"
    "${SR_TEXTURE_VENDOR_DIR}/KTX-Software/external/astc-encoder/Source"
    "${SR_TEXTURE_VENDOR_DIR}/etc2comp/EtcLib/Etc"
    "${SR_TEXTURE_VENDOR_DIR}/etc2comp/EtcLib/EtcCodec")
target_link_libraries(Engine PRIVATE CMP_Core ktx ${SR_TEXTURE_ASTC_TARGET} EtcLib)
set_target_properties(EtcLib CMP_Core PROPERTIES POSITION_INDEPENDENT_CODE ON)

file(READ "${SR_TEXTURE_VENDOR_DIR}/KTX-Software/external/astc-encoder/Source/astcenc.h" SR_ASTC_HEADER)
if(SR_ASTC_HEADER MATCHES "parent_context")
    target_compile_definitions(Engine PRIVATE SR_ASTCENC_HAS_PARENT_CONTEXT)
endif()

# Increment manually when encoder, mip generation, or container changes require re-encoding cached textures.
set(SR_TEXTURE_ENCODER_VERSION 1)
target_compile_definitions(Engine PRIVATE SR_TEXTURE_ENCODER_REVISION="${SR_TEXTURE_ENCODER_VERSION}")

# Increment for quality-check changes; this reruns validation without re-encoding blocks.
set(SR_TEXTURE_QUALITY_VERSION 1)
target_compile_definitions(Engine PRIVATE SR_TEXTURE_QUALITY_REVISION="${SR_TEXTURE_QUALITY_VERSION}")

option(SR_TEXTURE_USE_OPENCL "Enable host GPU BC encoders, with CPU fallback" ON)
if(SR_TEXTURE_USE_OPENCL)
    option(SR_TEXTURE_STATIC_OPENCL "Link the OpenCL ICD loader into the engine" ON)
    if(SR_TEXTURE_STATIC_OPENCL)
        include("${CMAKE_CURRENT_LIST_DIR}/OpenCLSDK.cmake")
        sr_install_texture_opencl()
    else()
        find_package(OpenCL QUIET)
        if(NOT TARGET OpenCL::OpenCL)
            include("${CMAKE_CURRENT_LIST_DIR}/OpenCLSDK.cmake")
            sr_install_texture_opencl()
        endif()
    endif()
endif()
if(SR_TEXTURE_USE_OPENCL AND TARGET OpenCL::OpenCL)
    function(SR_TEXTURE_EXPAND_KERNEL SR_KERNEL_FILE SR_OUTPUT)
        file(READ "${SR_KERNEL_FILE}" SR_KERNEL_SOURCE)
        get_filename_component(SR_KERNEL_DIRECTORY "${SR_KERNEL_FILE}" DIRECTORY)
        string(REGEX MATCHALL "#include[ \t]+\"[^\"]+\"" SR_KERNEL_INCLUDES "${SR_KERNEL_SOURCE}")
        foreach(SR_INCLUDE IN LISTS SR_KERNEL_INCLUDES)
            string(REGEX REPLACE "#include[ \t]+\"([^\"]+)\"" "\\1" SR_HEADER_NAME "${SR_INCLUDE}")
            if(EXISTS "${SR_KERNEL_DIRECTORY}/${SR_HEADER_NAME}")
                SR_TEXTURE_EXPAND_KERNEL("${SR_KERNEL_DIRECTORY}/${SR_HEADER_NAME}" SR_HEADER_SOURCE)
                string(REPLACE "${SR_INCLUDE}" "${SR_HEADER_SOURCE}" SR_KERNEL_SOURCE "${SR_KERNEL_SOURCE}")
            else()
                string(REPLACE "${SR_INCLUDE}" "" SR_KERNEL_SOURCE "${SR_KERNEL_SOURCE}")
            endif()
        endforeach()
        string(REGEX REPLACE "[^\n]*#include[^\n]*" "" SR_KERNEL_SOURCE "${SR_KERNEL_SOURCE}")
        string(REPLACE "[[maybe_unused]]" "" SR_KERNEL_SOURCE "${SR_KERNEL_SOURCE}")
        set(${SR_OUTPUT} "${SR_KERNEL_SOURCE}" PARENT_SCOPE)
    endfunction()
    set(SR_CL_CASES "")
    foreach(SR_BC_CODEC IN ITEMS 1 2 3 4 5 7)
        SR_TEXTURE_EXPAND_KERNEL("${SR_TEXTURE_VENDOR_DIR}/cmp_core/shaders/bc${SR_BC_CODEC}_encode_kernel.cpp" SR_CL_SOURCE)
        # OpenCL C uses ulong for 64-bit integers. Adapt the embedded copy only.
        string(REPLACE "typedef unsigned long long CGU_UINT64;" "typedef ulong CGU_UINT64;" SR_CL_SOURCE "${SR_CL_SOURCE}")
        # Shared vendor kernels contain C++ scalar casts; OpenCL C requires C casts.
        string(REGEX REPLACE "static_cast[ \t]*<[ \t]*([A-Za-z_][A-Za-z0-9_]*)[ \t]*>[ \t]*\\(" "(\\1)(" SR_CL_SOURCE "${SR_CL_SOURCE}")
        if(SR_BC_CODEC EQUAL 7)
            string(REPLACE "cmp_memsetBC7(&EncodeState,0,sizeof(EncodeState));"
                "cmp_memsetBC7((CGV_BYTE*)&EncodeState, 0, sizeof(EncodeState));" SR_CL_SOURCE "${SR_CL_SOURCE}")
            # Vendor default-option helpers are CPU-only. Initialize the device structure
            # directly, using the same defaults as SetDefaultBC7Options.
            string(APPEND SR_CL_SOURCE "\n__kernel void SRInitialize(__global uchar* storage, float quality, uint threshold) {
    BC7_Encode options = {0};
    options.quality = quality;
    options.minThreshold = 5.0f;
    options.maxThreshold = 80.0f;
    options.validModeMask = 0xFF;
    options.imageNeedsAlpha = true;
    options.channels = 4;
    options.part_count = 128;
    options.errorThreshold = options.maxThreshold * (1.0f - quality) + (quality > 0.5f ? options.minThreshold : 0.0f);
    *(__global BC7_Encode*)storage = options;
}\n")
        else()
            string(APPEND SR_CL_SOURCE "\n__kernel void SRInitialize(__global uchar* storage, float quality, uint threshold) {
    CMP_BC15Options options = {0};
    options.m_fquality = quality;
    options.m_fChannelWeights[0] = 0.3086f;
    options.m_fChannelWeights[1] = 0.6094f;
    options.m_fChannelWeights[2] = 0.0820f;
    options.m_nAlphaThreshold = threshold;
    options.m_nRefinementSteps = 1;
    options.m_src_width = 4;
    options.m_src_height = 4;
    *(__global CMP_BC15Options*)storage = options;
}\n")
        endif()
        string(APPEND SR_CL_CASES "            case ${SR_BC_CODEC}:\n")
        string(LENGTH "${SR_CL_SOURCE}" SR_CL_LENGTH)
        set(SR_CL_POSITION 0)
        while(SR_CL_POSITION LESS SR_CL_LENGTH)
            string(SUBSTRING "${SR_CL_SOURCE}" ${SR_CL_POSITION} 8000 SR_CL_CHUNK)
            string(APPEND SR_CL_CASES "                sources.emplace_back(R\"SR_COMPUTE(${SR_CL_CHUNK})SR_COMPUTE\");\n")
            math(EXPR SR_CL_POSITION "${SR_CL_POSITION} + 8000")
        endwhile()
        string(APPEND SR_CL_CASES "                return;\n")
    endforeach()
    configure_file("${CORE_ROOT_DIR}/cmake/TextureComputeSources.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/TextureTools/TextureComputeSources.h" @ONLY)
    target_include_directories(Engine PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/TextureTools")
    target_link_libraries(Engine PRIVATE OpenCL::OpenCL)
    target_compile_definitions(Engine PRIVATE SR_TEXTURE_OPENCL SR_TEXTURE_GPU_REVISION="cmp-opencl-v3")
else()
    target_compile_definitions(Engine PRIVATE SR_TEXTURE_GPU_REVISION="cpu-only")
    message(STATUS "[SpaRcle Engine] Texture export: OpenCL unavailable or disabled; using CPU encoders")
endif()
set(BUILD_SHARED_LIBS "${SR_TEXTURE_PREVIOUS_SHARED_LIBS}")
