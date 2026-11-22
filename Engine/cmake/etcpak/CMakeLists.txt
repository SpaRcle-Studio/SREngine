# Created by OpenAI Codex on 22.11.2026.

add_library(SRTextureEtcpak STATIC
    "${SR_ETCPAK_DIR}/ProcessRGB.cpp"
    "${SR_ETCPAK_DIR}/Dither.cpp"
    "${SR_ETCPAK_DIR}/Tables.cpp")
set_target_properties(SRTextureEtcpak PROPERTIES POSITION_INDEPENDENT_CODE ON
    DISABLE_PRECOMPILE_HEADERS ON UNITY_BUILD OFF)
target_compile_features(SRTextureEtcpak PRIVATE cxx_std_20)
if(MSVC)
    target_compile_definitions(SRTextureEtcpak PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
    target_compile_options(SRTextureEtcpak PRIVATE /O2 /Ob2)
else()
    target_compile_options(SRTextureEtcpak PRIVATE -O3)
endif()
