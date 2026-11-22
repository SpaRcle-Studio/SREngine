//
// Created by OpenAI Codex on 22.11.2026.
//

#include <Engine/Tests/TexturePipelineTest.h>
#include <Engine/Export/TextureQuality.h>

#include <Graphics/Loaders/TextureContainer.h>

#ifdef SR_COMMON_ZLIB
    #include <zlib/zlib.h>
#endif

#include <Codegen/TexturePipelineTest.generated.hpp>

namespace SR_CORE_NS::Tests {
    SR_UTILS_NS::TestExecutionResult TexturePipelineTest::Run() {
        SR_TRACY_ZONE;
        bool success = SR_GRAPH_NS::TextureContainer::GetLevelSize(5, 3, SR_GRAPH_NS::TextureCompression::BC1, SR_GRAPH_NS::ImageFormat::RGBA8_UNORM) == 16
            && SR_GRAPH_NS::TextureContainer::GetLevelSize(1, 1, SR_GRAPH_NS::TextureCompression::BC7, SR_GRAPH_NS::ImageFormat::RGBA8_UNORM) == 16
            && SR_GRAPH_NS::TextureContainer::GetLevelSize(7, 13, SR_GRAPH_NS::TextureCompression::ASTC6x6, SR_GRAPH_NS::ImageFormat::RGBA8_UNORM) == 96
            && SR_GRAPH_NS::TextureContainer::GetLevelSize(9, 1, SR_GRAPH_NS::TextureCompression::EACR11, SR_GRAPH_NS::ImageFormat::R8_UNORM) == 24
            && SR_GRAPH_NS::TextureContainer::FloatToHalf(1.f) == 0x3c00
            && SR_GRAPH_NS::TextureContainer::FloatToHalf(-2.f) == 0xc000
            && SR_GRAPH_NS::TextureContainer::FloatToHalf(0.00006103515625f) == 0x0400
            && SR_GRAPH_NS::TextureContainer::HashBytes("hello") == 0xa430d84680aabd0bull;

        // A native 4x4 BC7 KTX2: one DFD descriptor and one 16-byte block, no supercompression.
        SR_UTILS_NS::String fixture;
        fixture.resize(176);
        memset(fixture.data(), 0, fixture.size());
        const uint8_t identifier[] { 0xab, 0x4b, 0x54, 0x58, 0x20, 0x32, 0x30, 0xbb, 0x0d, 0x0a, 0x1a, 0x0a };
        memcpy(fixture.data(), identifier, sizeof(identifier));
        fixture[12] = static_cast<char>(145);
        fixture[16] = 1;
        fixture[20] = 4;
        fixture[24] = 4;
        fixture[36] = 1;
        fixture[40] = 1;
        fixture[48] = 104;
        fixture[52] = 44;
        fixture[80] = static_cast<char>(160);
        fixture[88] = 16;
        fixture[96] = 16;
        fixture[104] = 44;
        fixture[112] = 2;
        fixture[114] = 40;
        fixture[116] = static_cast<char>(134);
        fixture[117] = 1;
        fixture[118] = 1;
        fixture[120] = 3;
        fixture[121] = 3;
        fixture[124] = 16;
        fixture[134] = 127;
        fixture[160] = 64;
        SR_GRAPH_NS::PreparedTexture texture;
        success &= SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(fixture), texture)
            && texture.width == 4 && texture.height == 4 && texture.mips.size() == 1 && texture.mips[0].bytes.size() == 16;
        auto corrupt = fixture;
        corrupt[44] = 1;
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(corrupt), texture);
        corrupt = fixture;
        corrupt[88] = 8;
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(corrupt), texture);
        corrupt = fixture;
        corrupt[80] = 112;
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(corrupt), texture);
        corrupt = fixture;
        corrupt[120] = 7;
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(corrupt), texture);
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(fixture.data(), fixture.size() - 1), texture);
    #ifdef SR_COMMON_ZLIB
        uint8_t compressed[64]{};
        uLongf compressedSize = sizeof(compressed);
        success &= compress2(compressed, &compressedSize, reinterpret_cast<const Bytef*>(fixture.data() + 160), 16, 9) == Z_OK;
        auto deflated = fixture;
        deflated.resize(149);
        deflated[44] = 3;
        deflated[80] = static_cast<char>(149); // ZLIB levels do not require block alignment.
        deflated[88] = static_cast<char>(compressedSize);
        deflated.append(reinterpret_cast<const char*>(compressed), compressedSize);
        success &= SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(deflated), texture)
            && texture.mips.size() == 1 && texture.mips[0].bytes[0] == 64 && texture.mips[0].bytes.size() == 16;
        auto invalidDeflated = deflated;
        invalidDeflated[96] = 17;
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(invalidDeflated), texture);
        invalidDeflated = deflated;
        invalidDeflated.back() ^= 1;
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(invalidDeflated), texture);
        invalidDeflated = deflated;
        invalidDeflated[88] = static_cast<char>(compressedSize + 1);
        invalidDeflated.append("x", 1);
        success &= !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(invalidDeflated), texture);
    #endif

        SR_UTILS_NS::Vector<float_t> reference;
        reference.resize(128 * 128 * 4);
        std::fill(reference.begin(), reference.end(), 1.f);
        auto decoded = reference;
        success &= TextureQuality::Measure(reference, decoded, 128, 128, SR_GRAPH_NS::TextureCompressionPolicy::HighQuality).accepted;
        decoded[0] = decoded[1] = decoded[2] = 0.f;
        const auto localError = TextureQuality::Measure(reference, decoded, 128, 128, SR_GRAPH_NS::TextureCompressionPolicy::HighQuality);
        success &= localError.accepted && localError.colorPsnr > 40.f && localError.worstBlockRmse > 0.2f
            && localError.blockRmseP999 < 0.01f && localError.badBlockFraction > 0.f;
        decoded = reference;
        for (uint32_t x = 0; x < 16; x += 4) {
            decoded[x * 4] = decoded[x * 4 + 1] = decoded[x * 4 + 2] = 0.6f;
        }
        const auto distributedError = TextureQuality::Measure(reference, decoded, 128, 128, SR_GRAPH_NS::TextureCompressionPolicy::HighQuality);
        success &= !distributedError.accepted && distributedError.colorPsnr > 40.f && distributedError.blockRmseP999 > 0.08f;
        std::fill(reference.begin(), reference.end(), 0.f);
        std::fill(decoded.begin(), decoded.end(), 0.f);
        decoded[0] = 1.f; // Invisible RGB differences must not reject transparent artwork.
        success &= TextureQuality::Measure(reference, decoded, 128, 128, SR_GRAPH_NS::TextureCompressionPolicy::HighQuality).accepted;
        reference[0] = reference[1] = reference[2] = reference[3] = 1.f;
        success &= !TextureQuality::Measure(reference, decoded, 128, 128, SR_GRAPH_NS::TextureCompressionPolicy::HighQuality).accepted;
        if (!success) {
            SR_ERROR("TexturePipelineTest::Run() : texture layout, KTX2 validation or quality metric regression");
            return SR_UTILS_NS::TestExecutionResult::Error;
        }
        return SR_UTILS_NS::TestExecutionResult::Success;
    }
}
