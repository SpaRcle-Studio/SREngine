//
// Created by OpenAI Codex on 22.11.2026.
//

#include <Engine/Export/TextureExporter.h>
#include <Engine/Export/TextureGpuEncoder.h>
#include <Engine/Export/TextureQuality.h>

#include <Graphics/Loaders/TextureContainer.h>
#include <Graphics/Loaders/TextureLoader.h>

#include <Utils/FileSystem/FileSystem.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/TaskManager/TaskManager.h>

#ifdef SR_BUILD_TEXTURE_TOOLS
    #include <cmp_core.h>
    #include <ktx.h>
    #include <astcenc.h>
    #include <Etc.h>
    #include <EtcBlock4x4.h>
#endif

namespace SR_CORE_NS {
    struct TextureExporter::State {
        TextureGpuEncoder gpu;
    #ifdef SR_BUILD_TEXTURE_TOOLS
        astcenc_context* pAstc = nullptr;
        uint32_t astcBlock = 0;
        uint32_t encoderThreads = 1;
        float_t astcQuality = -1.f;
        bool astcSrgb = false;
        void* pBC7Decode = nullptr;

        ~State() {
            if (pBC7Decode) {
                DestroyOptionsBC7(pBC7Decode);
            }
            if (pAstc) {
                astcenc_context_free(pAstc);
            }
        }
    #endif
    };

    TextureExporter::TextureExporter()
        : m_pState(new State())
    { }

    TextureExporter::~TextureExporter() {
        delete m_pState;
    }
}

#ifdef SR_BUILD_TEXTURE_TOOLS
namespace SR_CORE_NS::TextureExportDetails {
    struct FloatMip {
        uint32_t width = 0;
        uint32_t height = 0;
        SR_UTILS_NS::Vector<float_t> pixels;
    };

    static uint8_t ToByte(float_t value) {
        return static_cast<uint8_t>(std::clamp(value, 0.f, 1.f) * 255.f + 0.5f);
    }

    static bool DecodeColor(const SR_GRAPH_NS::TextureMipData& mip, SR_GRAPH_NS::TextureCompression compression,
        SR_GRAPH_NS::ImageFormat format, const FloatMip& reference, const void* pBC7Options, SR_UTILS_NS::Vector<float_t>& pixels) {
        pixels.resize(uint64_t(mip.width) * mip.height * 4);
        if (compression >= SR_GRAPH_NS::TextureCompression::ASTC4x4 && compression <= SR_GRAPH_NS::TextureCompression::ASTC8x8) {
            const auto block = SR_GRAPH_NS::TextureContainer::GetBlockInfo(compression, format);
            astcenc_config config{};
            if (astcenc_config_init(format == SR_GRAPH_NS::ImageFormat::RGBA8_SRGB ? ASTCENC_PRF_LDR_SRGB : ASTCENC_PRF_LDR,
                block.width, block.height, 1, 0.f, ASTCENC_FLG_DECOMPRESS_ONLY, &config) != ASTCENC_SUCCESS) {
                return false;
            }
            astcenc_context* pAstc = nullptr;
        #ifdef SR_ASTCENC_HAS_PARENT_CONTEXT
            const auto allocation = astcenc_context_alloc(&config, 1, &pAstc, nullptr);
        #else
            const auto allocation = astcenc_context_alloc(&config, 1, &pAstc);
        #endif
            if (allocation != ASTCENC_SUCCESS) {
                return false;
            }
            void* pSlice = pixels.data();
            astcenc_image image { mip.width, mip.height, 1, ASTCENC_TYPE_F32, &pSlice };
            const astcenc_swizzle swizzle { ASTCENC_SWZ_R, ASTCENC_SWZ_G, ASTCENC_SWZ_B, ASTCENC_SWZ_A };
            const bool success = astcenc_decompress_image(pAstc, mip.bytes.data(), mip.bytes.size(), &image, &swizzle, 0) == ASTCENC_SUCCESS;
            astcenc_context_free(pAstc);
            return success;
        }
        if (compression == SR_GRAPH_NS::TextureCompression::ETC2RGB || compression == SR_GRAPH_NS::TextureCompression::ETC2RGBA) {
            const auto etcFormat = compression == SR_GRAPH_NS::TextureCompression::ETC2RGB ? Etc::Image::Format::RGB8 : Etc::Image::Format::RGBA8;
            Etc::Image source(const_cast<float_t*>(reference.pixels.data()), mip.width, mip.height, Etc::ErrorMetric::NUMERIC);
            Etc::Image image(etcFormat, mip.width, mip.height, const_cast<uint8_t*>(mip.bytes.data()),
                static_cast<uint32_t>(mip.bytes.size()), &source, Etc::ErrorMetric::NUMERIC);
            for (uint32_t index = 0; index < image.GetNumberOfBlocks(); ++index) {
                auto&& block = image.GetBlocks()[index];
                for (uint32_t y = 0; y < 4 && block.GetSourceV() + y < mip.height; ++y) {
                    for (uint32_t x = 0; x < 4 && block.GetSourceH() + x < mip.width; ++x) {
                        const uint64_t offset = (uint64_t(block.GetSourceV() + y) * mip.width + block.GetSourceH() + x) * 4;
                        const auto pixel = block.GetDecodedColors()[x * 4 + y];
                        pixels[offset] = pixel.fR;
                        pixels[offset + 1] = pixel.fG;
                        pixels[offset + 2] = pixel.fB;
                        pixels[offset + 3] = block.GetDecodedAlphas()[x * 4 + y];
                    }
                }
            }
            return true;
        }
        const uint32_t blockBytes = compression == SR_GRAPH_NS::TextureCompression::BC1 ? 8 : 16;
        const uint32_t columns = (mip.width + 3) / 4;
        for (uint32_t y = 0; y < mip.height; y += 4) {
            for (uint32_t x = 0; x < mip.width; x += 4) {
                const auto pBlock = mip.bytes.data() + (uint64_t(y / 4) * columns + x / 4) * blockBytes;
                uint8_t decoded[64]{};
                int32_t status = -1;
                switch (compression) {
                    case SR_GRAPH_NS::TextureCompression::BC1: status = DecompressBlockBC1(pBlock, decoded); break;
                    case SR_GRAPH_NS::TextureCompression::BC2: status = DecompressBlockBC2(pBlock, decoded); break;
                    case SR_GRAPH_NS::TextureCompression::BC3: status = DecompressBlockBC3(pBlock, decoded); break;
                    case SR_GRAPH_NS::TextureCompression::BC7: status = DecompressBlockBC7(pBlock, decoded, pBC7Options); break;
                    default: return false;
                }
                if (status != 0) {
                    return false;
                }
                for (uint32_t localY = 0; localY < 4 && y + localY < mip.height; ++localY) {
                    for (uint32_t localX = 0; localX < 4 && x + localX < mip.width; ++localX) {
                        for (uint32_t channel = 0; channel < 4; ++channel) {
                            pixels[((uint64_t(y + localY) * mip.width) + x + localX) * 4 + channel]
                                = decoded[(localY * 4 + localX) * 4 + channel] / 255.f;
                        }
                    }
                }
            }
        }
        return true;
    }

    static float_t ToLinear(float_t value) {
        return value <= 0.04045f ? value / 12.92f : std::pow((value + 0.055f) / 1.055f, 2.4f);
    }

    static float_t ToSrgb(float_t value) {
        return value <= 0.0031308f ? value * 12.92f : 1.055f * std::pow(value, 1.f / 2.4f) - 0.055f;
    }

    static void Normalize(float_t* pPixel) {
        float_t x = pPixel[0] * 2.f - 1.f;
        float_t y = pPixel[1] * 2.f - 1.f;
        float_t z = pPixel[2] * 2.f - 1.f;
        const float_t length = std::sqrt(x * x + y * y + z * z);
        if (length > 0.00001f) {
            x /= length;
            y /= length;
            z /= length;
        }
        else {
            x = y = 0.f;
            z = 1.f;
        }
        pPixel[0] = x * 0.5f + 0.5f;
        pPixel[1] = y * 0.5f + 0.5f;
        pPixel[2] = z * 0.5f + 0.5f;
    }

    static bool Decode(SR_UTILS_NS::StringView bytes, FloatMip& mip, bool& hdr) {
        SR_GRAPH_NS::TextureSourceInfo info;
        if (!SR_GRAPH_NS::TextureLoader::DecodeSource(bytes, info, mip.pixels)) {
            return false;
        }
        mip.width = info.width;
        mip.height = info.height;
        hdr = info.hdr;
        return true;
    }

    static float_t Coverage(const FloatMip& mip, float_t cutoff, float_t scale) {
        uint64_t covered = 0;
        for (uint64_t i = 3; i < mip.pixels.size(); i += 4) {
            covered += mip.pixels[i] * scale >= cutoff;
        }
        return static_cast<float_t>(covered) / (uint64_t(mip.width) * mip.height);
    }

    static FloatMip Downsample(const FloatMip& source, bool srgb, bool normal, bool coverage, float_t cutoff, float_t targetCoverage) {
        SR_TRACY_ZONE;
        FloatMip mip;
        mip.width = std::max(1u, source.width / 2);
        mip.height = std::max(1u, source.height / 2);
        mip.pixels.resize(uint64_t(mip.width) * mip.height * 4);
        for (uint32_t y = 0; y < mip.height; ++y) {
            for (uint32_t x = 0; x < mip.width; ++x) {
                auto&& pDestination = mip.pixels.data() + (uint64_t(y) * mip.width + x) * 4;
                const uint32_t beginX = uint64_t(x) * source.width / mip.width;
                const uint32_t endX = uint64_t(x + 1) * source.width / mip.width;
                const uint32_t beginY = uint64_t(y) * source.height / mip.height;
                const uint32_t endY = uint64_t(y + 1) * source.height / mip.height;
                for (uint32_t sy = beginY; sy < endY; ++sy) {
                    for (uint32_t sx = beginX; sx < endX; ++sx) {
                        const auto&& pSource = source.pixels.data() + (uint64_t(sy) * source.width + sx) * 4;
                        for (uint32_t channel = 0; channel < 4; ++channel) {
                            pDestination[channel] += srgb && channel < 3 ? ToLinear(pSource[channel]) : pSource[channel];
                        }
                    }
                }
                const float_t samples = (endX - beginX) * (endY - beginY);
                for (uint32_t channel = 0; channel < 4; ++channel) {
                    pDestination[channel] /= samples;
                    if (srgb && channel < 3) {
                        pDestination[channel] = ToSrgb(pDestination[channel]);
                    }
                }
                if (normal) {
                    Normalize(pDestination);
                }
            }
        }
        if (coverage) {
            float_t low = 0.f;
            float_t high = 16.f;
            float_t best = 1.f;
            float_t bestError = std::abs(Coverage(mip, cutoff, best) - targetCoverage);
            for (uint32_t iteration = 0; iteration < 20; ++iteration) {
                const float_t scale = (low + high) * 0.5f;
                const float_t current = Coverage(mip, cutoff, scale);
                const float_t error = std::abs(current - targetCoverage);
                if (error < bestError) {
                    bestError = error;
                    best = scale;
                }
                if (current < targetCoverage) {
                    low = scale;
                }
                else {
                    high = scale;
                }
            }
            for (uint64_t i = 3; i < mip.pixels.size(); i += 4) {
                mip.pixels[i] = std::clamp(mip.pixels[i] * best, 0.f, 1.f);
            }
        }
        return mip;
    }

    static bool EncodeBC(const FloatMip& mip, SR_GRAPH_NS::TextureCompression compression, float_t quality, float_t cutoff, uint32_t threadCount,
        SR_UTILS_NS::Vector<uint8_t>& output, const SR_HTYPES_NS::Function<bool()>& cancelled,
        const SR_HTYPES_NS::Function<void(float_t)>& progress) {
        SR_TRACY_ZONE;
        const uint32_t columns = (mip.width + 3) / 4;
        const uint32_t rows = (mip.height + 3) / 4;
        const uint32_t blockBytes = compression == SR_GRAPH_NS::TextureCompression::BC1 || compression == SR_GRAPH_NS::TextureCompression::BC4 ? 8 : 16;
        output.resize(uint64_t(columns) * rows * blockBytes);
        std::atomic<bool> failed = false;
        std::atomic<uint32_t> completedRows = 0;
        std::mutex progressMutex;
        auto lastProgress = std::chrono::steady_clock::now();
        const uint32_t jobs = std::min(threadCount, rows);
        SR_UTILS_NS::Vector<uint64_t> tasks;
        for (uint32_t job = 0; job < jobs; ++job) {
            tasks.emplace_back(SR_UTILS_NS::TaskManager::Instance().ExecuteParallel([&, job](auto&&) {
                void* pOptions = nullptr;
                int32_t result = 1;
                static std::mutex initializationMutex;
                {
                    std::lock_guard lock(initializationMutex);
                    switch (compression) {
                    case SR_GRAPH_NS::TextureCompression::BC1: result = CreateOptionsBC1(&pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC2: result = CreateOptionsBC2(&pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC3: result = CreateOptionsBC3(&pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC4: result = CreateOptionsBC4(&pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC5: result = CreateOptionsBC5(&pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC6: result = CreateOptionsBC6(&pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC7: result = CreateOptionsBC7(&pOptions); break;
                        default: break;
                    }
                }
                if (result || !pOptions) {
                    SR_ERROR("TextureExportDetails::EncodeBC() : failed to initialize codec {}, error {}", static_cast<uint32_t>(compression), result);
                    failed = true;
                    return;
                }
                switch (compression) {
                    case SR_GRAPH_NS::TextureCompression::BC1: SetQualityBC1(pOptions, quality); SetAlphaThresholdBC1(pOptions, ToByte(cutoff)); break;
                    case SR_GRAPH_NS::TextureCompression::BC2: SetQualityBC2(pOptions, quality); break;
                    case SR_GRAPH_NS::TextureCompression::BC3: SetQualityBC3(pOptions, quality); break;
                    case SR_GRAPH_NS::TextureCompression::BC4: SetQualityBC4(pOptions, quality); break;
                    case SR_GRAPH_NS::TextureCompression::BC5: SetQualityBC5(pOptions, quality); break;
                    case SR_GRAPH_NS::TextureCompression::BC6: SetQualityBC6(pOptions, quality); SetSignedBC6(pOptions, true); break;
                    case SR_GRAPH_NS::TextureCompression::BC7: SetQualityBC7(pOptions, quality); SetAlphaOptionsBC7(pOptions, true, false, false); break;
                    default: break;
                }
                for (uint32_t row = job; row < rows && !failed; row += jobs) {
                    if (cancelled && cancelled()) {
                        failed = true;
                        break;
                    }
                    for (uint32_t column = 0; column < columns; ++column) {
                        uint8_t rgba[64];
                        uint8_t red[16];
                        uint8_t green[16];
                        uint16_t rgbHalf[48];
                        for (uint32_t y = 0; y < 4; ++y) {
                            for (uint32_t x = 0; x < 4; ++x) {
                                const uint32_t pixel = y * 4 + x;
                                const auto&& pPixel = mip.pixels.data() + (uint64_t(std::min(row * 4 + y, mip.height - 1)) * mip.width
                                    + std::min(column * 4 + x, mip.width - 1)) * 4;
                                for (uint32_t channel = 0; channel < 4; ++channel) {
                                    rgba[pixel * 4 + channel] = ToByte(pPixel[channel]);
                                }
                                for (uint32_t channel = 0; channel < 3; ++channel) {
                                    rgbHalf[pixel * 3 + channel] = SR_GRAPH_NS::TextureContainer::FloatToHalf(pPixel[channel]);
                                }
                                red[pixel] = rgba[pixel * 4];
                                green[pixel] = rgba[pixel * 4 + 1];
                            }
                        }
                        auto&& pDestination = output.data() + (uint64_t(row) * columns + column) * blockBytes;
                        switch (compression) {
                            case SR_GRAPH_NS::TextureCompression::BC1: result = CompressBlockBC1(rgba, 16, pDestination, pOptions); break;
                            case SR_GRAPH_NS::TextureCompression::BC2: result = CompressBlockBC2(rgba, 16, pDestination, pOptions); break;
                            case SR_GRAPH_NS::TextureCompression::BC3: result = CompressBlockBC3(rgba, 16, pDestination, pOptions); break;
                            case SR_GRAPH_NS::TextureCompression::BC4: result = CompressBlockBC4(red, 4, pDestination, pOptions); break;
                            case SR_GRAPH_NS::TextureCompression::BC5: result = CompressBlockBC5(red, 4, green, 4, pDestination, pOptions); break;
                            case SR_GRAPH_NS::TextureCompression::BC6: result = CompressBlockBC6(rgbHalf, 12, pDestination, pOptions); break;
                            case SR_GRAPH_NS::TextureCompression::BC7: result = CompressBlockBC7(rgba, 16, pDestination, pOptions); break;
                            default: result = 1; break;
                        }
                        if (result) {
                            SR_ERROR("TextureExportDetails::EncodeBC() : codec {} failed at block ({}, {}), image {}x{}, error {}",
                                static_cast<uint32_t>(compression), column, row, mip.width, mip.height, result);
                            failed = true;
                            break;
                        }
                    }
                    ++completedRows;
                    if (progress) {
                        std::lock_guard lock(progressMutex);
                        const auto now = std::chrono::steady_clock::now();
                        if (completedRows == rows || now - lastProgress >= std::chrono::milliseconds(100)) {
                            progress(static_cast<float_t>(completedRows.load()) / rows);
                            lastProgress = now;
                        }
                    }
                }
                switch (compression) {
                    case SR_GRAPH_NS::TextureCompression::BC1: DestroyOptionsBC1(pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC2: DestroyOptionsBC2(pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC3: DestroyOptionsBC3(pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC4: DestroyOptionsBC4(pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC5: DestroyOptionsBC5(pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC6: DestroyOptionsBC6(pOptions); break;
                    case SR_GRAPH_NS::TextureCompression::BC7: DestroyOptionsBC7(pOptions); break;
                    default: break;
                }
            }, SR_UTILS_NS::TaskPriority::Normal));
        }
        for (const uint64_t task : tasks) {
            SR_UTILS_NS::TaskManager::Instance().Wait(task);
        }
        return !failed;
    }

    static void ApplyBC1Alpha(const FloatMip& mip, float_t cutoff, SR_UTILS_NS::Vector<uint8_t>& output) {
        const uint32_t columns = (mip.width + 3) / 4;
        const uint32_t rows = (mip.height + 3) / 4;
        for (uint32_t row = 0; row < rows; ++row) {
            for (uint32_t column = 0; column < columns; ++column) {
                bool transparent = false;
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 4; ++x) {
                        const uint64_t pixel = uint64_t(std::min(row * 4 + y, mip.height - 1)) * mip.width
                            + std::min(column * 4 + x, mip.width - 1);
                        transparent |= mip.pixels[pixel * 4 + 3] < cutoff;
                    }
                }
                auto&& pBlock = output.data() + (uint64_t(row) * columns + column) * 8;
                uint16_t first = uint16_t(pBlock[0]) | (uint16_t(pBlock[1]) << 8);
                uint16_t second = uint16_t(pBlock[2]) | (uint16_t(pBlock[3]) << 8);
                if ((transparent && first > second) || (!transparent && first < second)) {
                    std::swap(first, second);
                }
                if (!transparent && first == second) {
                    if (first < 65535) {
                        ++first;
                    }
                    else {
                        --second;
                    }
                }
                float_t colors[4][3]{};
                for (uint32_t i = 0; i < 2; ++i) {
                    const uint16_t endpoint = i == 0 ? first : second;
                    colors[i][0] = ((endpoint >> 11) & 31) / 31.f;
                    colors[i][1] = ((endpoint >> 5) & 63) / 63.f;
                    colors[i][2] = (endpoint & 31) / 31.f;
                }
                for (uint32_t channel = 0; channel < 3; ++channel) {
                    colors[2][channel] = transparent ? (colors[0][channel] + colors[1][channel]) * 0.5f
                        : (colors[0][channel] * 2.f + colors[1][channel]) / 3.f;
                    colors[3][channel] = (colors[0][channel] + colors[1][channel] * 2.f) / 3.f;
                }
                uint32_t indices = 0;
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 4; ++x) {
                        const auto&& pPixel = mip.pixels.data() + (uint64_t(std::min(row * 4 + y, mip.height - 1)) * mip.width
                            + std::min(column * 4 + x, mip.width - 1)) * 4;
                        uint32_t index = 3;
                        if (pPixel[3] >= cutoff) {
                            float_t bestError = 4.f;
                            for (uint32_t candidate = 0; candidate < (transparent ? 3u : 4u); ++candidate) {
                                float_t error = 0.f;
                                for (uint32_t channel = 0; channel < 3; ++channel) {
                                    const float_t difference = pPixel[channel] - colors[candidate][channel];
                                    error += difference * difference;
                                }
                                if (error < bestError) {
                                    bestError = error;
                                    index = candidate;
                                }
                            }
                        }
                        indices |= index << ((y * 4 + x) * 2);
                    }
                }
                pBlock[0] = static_cast<uint8_t>(first);
                pBlock[1] = static_cast<uint8_t>(first >> 8);
                pBlock[2] = static_cast<uint8_t>(second);
                pBlock[3] = static_cast<uint8_t>(second >> 8);
                for (uint32_t i = 0; i < 4; ++i) {
                    pBlock[4 + i] = static_cast<uint8_t>(indices >> (i * 8));
                }
            }
        }
    }

    static bool WriteKtx(const SR_GRAPH_NS::PreparedTexture& texture, SR_UTILS_NS::String& bytes) {
        ktxTextureCreateInfo info{};
        info.vkFormat = SR_GRAPH_NS::TextureContainer::GetNativeFormat(texture.compression, texture.format);
        info.baseWidth = texture.width;
        info.baseHeight = texture.height;
        info.baseDepth = 1;
        info.numDimensions = 2;
        info.numLevels = static_cast<uint32_t>(texture.mips.size());
        info.numLayers = 1;
        info.numFaces = 1;
        ktxTexture2* pTexture = nullptr;
        if (ktxTexture2_Create(&info, KTX_TEXTURE_CREATE_ALLOC_STORAGE, &pTexture) != KTX_SUCCESS) {
            return false;
        }
        bool success = true;
        for (uint32_t level = 0; level < texture.mips.size(); ++level) {
            auto&& mip = texture.mips[level];
            success &= ktxTexture_SetImageFromMemory(ktxTexture(pTexture), level, 0, 0, mip.bytes.data(), mip.bytes.size()) == KTX_SUCCESS;
        }
    #ifdef SR_COMMON_ZLIB
        success = success && ktxTexture2_DeflateZLIB(pTexture, 9) == KTX_SUCCESS;
    #endif
        ktx_uint8_t* pBytes = nullptr;
        ktx_size_t size = 0;
        success = success && ktxTexture2_WriteToMemory(pTexture, &pBytes, &size) == KTX_SUCCESS;
        if (success) {
            bytes = SR_UTILS_NS::String(SR_UTILS_NS::StringView(reinterpret_cast<const char*>(pBytes), size));
        }
        free(pBytes);
        ktxTexture_Destroy(ktxTexture(pTexture));
        return success;
    }
}
#endif

namespace SR_CORE_NS {
    bool TextureExporter::Prepare(const SR_UTILS_NS::Path& source, SR_GRAPH_NS::ImageMetaInfo& metadata,
        SR_GRAPH_NS::TextureExportProfile profile, const SR_UTILS_NS::Path& buildRoot,
        SR_UTILS_NS::Vector<TextureBuildArtifact>& artifacts) {
        SR_TRACY_ZONE;
    #ifndef SR_BUILD_TEXTURE_TOOLS
        SR_ERROR("TextureExporter::Prepare() : enable SR_BUILD_TEXTURE_TOOLS and install texture encoder dependencies to export {}", source);
        return false;
    #else
        if (isCancelled && isCancelled()) {
            return false;
        }
        uint32_t encoderThreadCount = 1;
    #ifdef SR_THREADS_ALLOWED
        const uint32_t availableThreads = std::max(1u, std::thread::hardware_concurrency());
        encoderThreadCount = static_cast<uint32_t>(std::max(uint64_t(1),
            uint64_t(availableThreads) * std::clamp(cpuUsagePercent, 1u, 100u) / 100));
    #endif
        if (m_pState->encoderThreads != encoderThreadCount) {
            if (m_pState->pAstc) {
                astcenc_context_free(m_pState->pAstc);
                m_pState->pAstc = nullptr;
            }
            m_pState->encoderThreads = encoderThreadCount;
        }
        SR_UTILS_NS::String sourceBytes;
        if (!SR_UTILS_NS::FileSystem::ReadFile(source, sourceBytes)) {
            SR_ERROR("TextureExporter::Prepare() : cannot read {}", source);
            return false;
        }
        if (!std::isfinite(metadata.compressionQuality) || !std::isfinite(metadata.alphaCutoff)) {
            SR_ERROR("TextureExporter::Prepare() : invalid compression parameters for {}", source);
            return false;
        }
        auto policy = metadata.compressionPolicy;
        if (policy == SR_GRAPH_NS::TextureCompressionPolicy::Auto) {
            policy = metadata.content == SR_GRAPH_NS::TextureContent::Illustration
                ? SR_GRAPH_NS::TextureCompressionPolicy::HighQuality
                : metadata.content == SR_GRAPH_NS::TextureContent::Interface || metadata.imageType == SR_GRAPH_NS::ImageType::UI
                    ? SR_GRAPH_NS::TextureCompressionPolicy::Lossless : SR_GRAPH_NS::TextureCompressionPolicy::Balanced;
        }
        const float_t quality = policy == SR_GRAPH_NS::TextureCompressionPolicy::HighQuality
            ? std::max(0.8f, std::clamp(metadata.compressionQuality, 0.f, 1.f)) : std::clamp(metadata.compressionQuality, 0.f, 1.f);
        const float_t cutoff = std::clamp(metadata.alphaCutoff, 0.001f, 0.999f);
        SR_GRAPH_NS::TextureSourceInfo sourceInfo;
        if (!SR_GRAPH_NS::TextureLoader::ReadSourceInfo(sourceBytes, sourceInfo)) {
            SR_ERROR("TextureExporter::Prepare() : invalid source image {}", source);
            return false;
        }
        const bool hdr = metadata.imageType == SR_GRAPH_NS::ImageType::HDR || sourceInfo.hdr;
        const bool normal = metadata.imageType == SR_GRAPH_NS::ImageType::Normal;
        const bool color = metadata.imageType == SR_GRAPH_NS::ImageType::Albedo || metadata.imageType == SR_GRAPH_NS::ImageType::Emissive
            || metadata.imageType == SR_GRAPH_NS::ImageType::UI;
        const bool srgb = !hdr && color && (metadata.format == SR_GRAPH_NS::ImageFormat::RGBA8_SRGB
            || metadata.format == SR_GRAPH_NS::ImageFormat::RGB8_SRGB
            || (metadata.format == SR_GRAPH_NS::ImageFormat::Auto && metadata.imageType != SR_GRAPH_NS::ImageType::UI));
        const auto format = hdr ? SR_GRAPH_NS::ImageFormat::RGBA16_SFLOAT
            : (srgb ? SR_GRAPH_NS::ImageFormat::RGBA8_SRGB : SR_GRAPH_NS::ImageFormat::RGBA8_UNORM);
        SR_UTILS_NS::Vector<SR_GRAPH_NS::TextureCompression> formats;
        const bool lossless = (hdr && !metadata.disableAlphaChannel && (sourceInfo.channels == 2 || sourceInfo.channels == 4))
            || policy == SR_GRAPH_NS::TextureCompressionPolicy::Disabled || policy == SR_GRAPH_NS::TextureCompressionPolicy::Lossless || metadata.cpuUsage
            || metadata.imageType == SR_GRAPH_NS::ImageType::MSDF || metadata.imageType == SR_GRAPH_NS::ImageType::PixelArt;
        if (!lossless && profile != SR_GRAPH_NS::TextureExportProfile::Universal) {
            if (metadata.compressionPolicy == SR_GRAPH_NS::TextureCompressionPolicy::Explicit) {
                formats.emplace_back(metadata.compression);
            }
            else if (profile == SR_GRAPH_NS::TextureExportProfile::Desktop) {
                if (color && !hdr && (policy == SR_GRAPH_NS::TextureCompressionPolicy::Balanced || policy == SR_GRAPH_NS::TextureCompressionPolicy::Aggressive)) {
                    formats.emplace_back(metadata.disableAlphaChannel || sourceInfo.channels == 1 || sourceInfo.channels == 3
                        ? SR_GRAPH_NS::TextureCompression::BC1 : SR_GRAPH_NS::TextureCompression::BC3);
                }
                formats.emplace_back(hdr ? SR_GRAPH_NS::TextureCompression::BC6
                    : normal ? SR_GRAPH_NS::TextureCompression::BC5
                    : (metadata.imageType == SR_GRAPH_NS::ImageType::Mask || metadata.imageType == SR_GRAPH_NS::ImageType::Roughness
                        || metadata.imageType == SR_GRAPH_NS::ImageType::Metallic || metadata.imageType == SR_GRAPH_NS::ImageType::AmbientOcclusion)
                        ? SR_GRAPH_NS::TextureCompression::BC4 : SR_GRAPH_NS::TextureCompression::BC7);
            }
            else if (!hdr) {
                formats.emplace_back(policy == SR_GRAPH_NS::TextureCompressionPolicy::HighQuality ? SR_GRAPH_NS::TextureCompression::ASTC4x4
                    : policy == SR_GRAPH_NS::TextureCompressionPolicy::Aggressive ? SR_GRAPH_NS::TextureCompression::ASTC8x8 : SR_GRAPH_NS::TextureCompression::ASTC6x6);
                formats.emplace_back(normal ? SR_GRAPH_NS::TextureCompression::EACRG11
                    : (metadata.imageType == SR_GRAPH_NS::ImageType::Mask ? SR_GRAPH_NS::TextureCompression::EACR11
                        : (metadata.disableAlphaChannel || sourceInfo.channels == 1 || sourceInfo.channels == 3)
                            ? SR_GRAPH_NS::TextureCompression::ETC2RGB : SR_GRAPH_NS::TextureCompression::ETC2RGBA));
            }
        }
        for (auto iterator = formats.begin(); iterator != formats.end();) {
            const bool astc = *iterator >= SR_GRAPH_NS::TextureCompression::ASTC4x4
                && *iterator <= SR_GRAPH_NS::TextureCompression::ASTC8x8;
            const bool etc2 = *iterator >= SR_GRAPH_NS::TextureCompression::ETC2RGB
                && *iterator <= SR_GRAPH_NS::TextureCompression::EACRG11;
            if ((astc && !useAstc) || (etc2 && !useEtc2)) {
                iterator = formats.erase(iterator);
            }
            else {
                ++iterator;
            }
        }
        if (formats.empty() || formats.back() != SR_GRAPH_NS::TextureCompression::None) {
            formats.emplace_back(SR_GRAPH_NS::TextureCompression::None);
        }
        metadata.preparedVariants.clear();
        metadata.preparedHashes.clear();
        metadata.compressed = false;
        const uint64_t sourceHash = SR_GRAPH_NS::TextureContainer::HashBytes(sourceBytes);
        const bool checkQuality = !hdr && color && metadata.qualityValidation != SR_GRAPH_NS::TextureQualityValidation::Off && !lossless;
        SR_UTILS_NS::String sourceExtension(source.GetExtensionView());
        for (char& character : sourceExtension) {
            if (character >= 'A' && character <= 'Z') {
                character = static_cast<char>(character - 'A' + 'a');
            }
        }
        const bool sourceFallback = (sourceExtension == "png" || sourceExtension == "jpg" || sourceExtension == "jpeg")
            && !hdr && !sourceInfo.sixteenBit && !normal && metadata.mipLevels == 1
            && !metadata.preserveAlphaCoverage && (metadata.format == SR_GRAPH_NS::ImageFormat::RGBA8_UNORM
                || metadata.format == SR_GRAPH_NS::ImageFormat::RGBA8_SRGB
                || (metadata.format == SR_GRAPH_NS::ImageFormat::Auto && (color || metadata.imageType == SR_GRAPH_NS::ImageType::MSDF
                    || metadata.imageType == SR_GRAPH_NS::ImageType::PixelArt || metadata.imageType == SR_GRAPH_NS::ImageType::ORM)));
        SR_UTILS_NS::Vector<TextureExportDetails::FloatMip> mips;
        bool desktopCompressedSelected = false;
    #ifdef SR_COMMON_ZLIB
        static constexpr SR_UTILS_NS::StringView storageCodec = "zlib";
    #else
        static constexpr SR_UTILS_NS::StringView storageCodec = "native";
    #endif
        for (uint32_t variantIndex = 0; variantIndex < formats.size(); ++variantIndex) {
            const auto compression = formats[variantIndex];
            auto reportVariantProgress = [&](float_t progress) {
                if (onProgress) {
                    onProgress((variantIndex + std::clamp(progress, 0.f, 1.f)) / static_cast<float_t>(formats.size()));
                }
            };
            reportVariantProgress(0.f);
            if (isCancelled && isCancelled()) {
                return false;
            }
            if (desktopCompressedSelected && compression != SR_GRAPH_NS::TextureCompression::None) {
                continue;
            }
            if (compression == SR_GRAPH_NS::TextureCompression::None && sourceFallback) {
                const auto relative = source.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
                const auto output = buildRoot.Concat("TextureCache").Concat("{}"_format(sourceHash)).Concat(relative);
                SR_UTILS_NS::String existing;
                const bool cached = SR_UTILS_NS::FileSystem::ReadFile(output, existing)
                    && SR_GRAPH_NS::TextureContainer::HashBytes(existing) == sourceHash;
                if (!cached && !SR_UTILS_NS::VFS::Instance().WriteFileAtomic(output, sourceBytes)) {
                    return false;
                }
                if (onStatus) {
                    onStatus("{} {} (lossless source)"_format(cached ? "Reusing" : "Staging", relative));
                }
                artifacts.emplace_back(TextureBuildArtifact { relative, output });
                metadata.preparedVariants.emplace_back(relative);
                metadata.preparedHashes.emplace_back(sourceHash);
                reportVariantProgress(1.f);
                continue;
            }
            const bool bc = compression >= SR_GRAPH_NS::TextureCompression::BC1 && compression <= SR_GRAPH_NS::TextureCompression::BC7;
            const auto block = SR_GRAPH_NS::TextureContainer::GetBlockInfo(compression, format);
            if (requireBlockAlignedTextures && (sourceInfo.width % block.width || sourceInfo.height % block.height)) {
                continue;
            }
            if ((profile == SR_GRAPH_NS::TextureExportProfile::Mobile && bc)
                || (profile == SR_GRAPH_NS::TextureExportProfile::Desktop && !bc && compression != SR_GRAPH_NS::TextureCompression::None)
                || (hdr && compression != SR_GRAPH_NS::TextureCompression::BC6 && compression != SR_GRAPH_NS::TextureCompression::None)) {
                SR_ERROR("TextureExporter::Prepare() : explicitly selected compression is incompatible with the target: {}", source);
                return false;
            }
            const auto relative = source.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
            const auto variant = relative.ConcatExt(SR_GRAPH_NS::TextureContainer::GetExtension(compression, format));
            const SR_UTILS_NS::String settings = "texture-pipeline-v4:{}:{}:{}:{}:{}:{}:{}:{}:{}:{}:{}:{}:{}:{}:{}"_format(
                static_cast<uint32_t>(compression), static_cast<uint32_t>(format), quality, metadata.mipLevels,
                static_cast<uint32_t>(metadata.imageType), metadata.disableAlphaChannel, metadata.preserveAlphaCoverage,
                cutoff, useGpu, SR_TEXTURE_ENCODER_REVISION, SR_TEXTURE_GPU_REVISION,
                useGpu && bc ? m_pState->gpu.GetIdentity() : SR_UTILS_NS::String("cpu"),
                static_cast<uint32_t>(policy), static_cast<uint32_t>(metadata.content), storageCodec);
            const uint64_t hash = SR_GRAPH_NS::TextureContainer::HashBytes(settings, sourceHash);
            const auto output = buildRoot.Concat("TextureCache").Concat("{}"_format(hash)).Concat(variant);
            const auto receipt = output.ConcatExt(".hash");
            SR_UTILS_NS::String existing;
            SR_UTILS_NS::String savedHash;
            SR_GRAPH_NS::PreparedTexture validated;
            const bool cached = output.IsFile() && receipt.IsFile() && SR_UTILS_NS::FileSystem::ReadFile(output, existing)
                && SR_UTILS_NS::FileSystem::ReadFile(receipt, savedHash)
                && (savedHash == "{}:{}"_format(hash, SR_GRAPH_NS::TextureContainer::HashBytes(existing))
                    || savedHash == "{}:{}:accepted"_format(hash, SR_GRAPH_NS::TextureContainer::HashBytes(existing))
                    || savedHash == "{}:{}:rejected"_format(hash, SR_GRAPH_NS::TextureContainer::HashBytes(existing)))
                && SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(existing), validated)
                && validated.compression == compression
                && SR_GRAPH_NS::TextureContainer::GetNativeFormat(validated.compression, validated.format)
                    == SR_GRAPH_NS::TextureContainer::GetNativeFormat(compression, format);
            uint64_t outputHash = cached ? SR_GRAPH_NS::TextureContainer::HashBytes(existing) : 0;
            const bool validateQuality = checkQuality && compression != SR_GRAPH_NS::TextureCompression::None;
            const auto qualityReceipt = output.ConcatExt(".quality");
            const auto qualityKey = "{}:{}:{}"_format(SR_TEXTURE_QUALITY_REVISION, static_cast<uint32_t>(policy), outputHash);
            SR_UTILS_NS::String savedQuality;
            const bool qualityCached = cached && validateQuality && SR_UTILS_NS::FileSystem::ReadFile(qualityReceipt, savedQuality)
                && (savedQuality == "{}:passed"_format(qualityKey) || savedQuality == "{}:failed"_format(qualityKey));
            bool qualityPassed = !qualityCached || savedQuality == "{}:passed"_format(qualityKey);
            if (onStatus) {
                onStatus("{} {} ({})"_format(cached ? "Reusing" : "Encoding", relative, SR_GRAPH_NS::TextureContainer::GetExtension(compression, format)));
            }
            const auto started = std::chrono::steady_clock::now();
            uint32_t gpuMips = 0;
            if (!cached || (validateQuality && !qualityCached)) {
                if (mips.empty()) {
                    TextureExportDetails::FloatMip base;
                    bool decodedHdr = false;
                    if (!TextureExportDetails::Decode(sourceBytes, base, decodedHdr)) {
                        SR_ERROR("TextureExporter::Prepare() : failed to decode {}", source);
                        return false;
                    }
                    for (uint64_t pixel = 0; pixel < base.pixels.size(); pixel += 4) {
                        if (metadata.disableAlphaChannel) {
                            base.pixels[pixel + 3] = 1.f;
                        }
                        if (normal) {
                            TextureExportDetails::Normalize(base.pixels.data() + pixel);
                        }
                    }
                    const float_t targetCoverage = TextureExportDetails::Coverage(base, cutoff, 1.f);
                    uint32_t levels = 1;
                    for (uint32_t dimension = std::max(base.width, base.height); dimension > 1; dimension /= 2) {
                        ++levels;
                    }
                    levels = metadata.mipLevels ? std::min(levels, metadata.mipLevels) : levels;
                    mips.emplace_back(std::move(base));
                    for (uint32_t level = 1; level < levels; ++level) {
                        if (isCancelled && isCancelled()) {
                            return false;
                        }
                        mips.emplace_back(TextureExportDetails::Downsample(mips.back(), srgb, normal,
                            metadata.preserveAlphaCoverage && !metadata.disableAlphaChannel, cutoff, targetCoverage));
                    }
                }
            }
            if (!cached) {
                SR_GRAPH_NS::PreparedTexture texture;
                texture.width = mips.front().width;
                texture.height = mips.front().height;
                texture.compression = compression;
                texture.format = format;
                bool gpuFallbackReported = false;
                uint64_t totalMipPixels = 0;
                uint64_t completedMipPixels = 0;
                for (auto&& mip : mips) {
                    totalMipPixels += uint64_t(mip.width) * mip.height;
                }
                for (auto&& mip : mips) {
                    if (isCancelled && isCancelled()) {
                        return false;
                    }
                    auto&& encoded = texture.mips.emplace_back();
                    encoded.width = mip.width;
                    encoded.height = mip.height;
                    encoded.bytes.resize(SR_GRAPH_NS::TextureContainer::GetLevelSize(mip.width, mip.height, compression, format));
                    bool success = true;
                    SR_HTYPES_NS::Function<void(float_t)> mipProgress = [&](float_t progress) {
                        reportVariantProgress(0.85f * static_cast<float_t>(completedMipPixels + uint64_t(mip.width) * mip.height * progress)
                            / static_cast<float_t>(totalMipPixels));
                    };
                    const bool encodedOnGpu = useGpu && bc && m_pState->gpu.Encode(mip.width, mip.height,
                        mip.pixels, compression, quality, cutoff, encoded.bytes, isCancelled, mipProgress);
                    if (isCancelled && isCancelled()) {
                        return false;
                    }
                    if (encodedOnGpu) {
                        ++gpuMips;
                    }
                    if (!encodedOnGpu && useGpu && compression != SR_GRAPH_NS::TextureCompression::None && !gpuFallbackReported) {
                        if (bc && compression != SR_GRAPH_NS::TextureCompression::BC6) {
                            SR_INFO("TextureExporter::Prepare() : GPU encoder unavailable or failed; using CPU for {}", variant);
                        }
                        else {
                            SR_INFO("TextureExporter::Prepare() : GPU encoding is not implemented for compression {}; using CPU for {}",
                                static_cast<uint32_t>(compression), variant);
                        }
                        gpuFallbackReported = true;
                    }
                    if (!encodedOnGpu && compression == SR_GRAPH_NS::TextureCompression::None) {
                        for (uint64_t i = 0; i < mip.pixels.size(); ++i) {
                            if (hdr) {
                                const uint16_t half = SR_GRAPH_NS::TextureContainer::FloatToHalf(mip.pixels[i]);
                                memcpy(encoded.bytes.data() + i * 2, &half, sizeof(half));
                            }
                            else {
                                encoded.bytes[i] = TextureExportDetails::ToByte(mip.pixels[i]);
                            }
                        }
                    }
                    else if (!encodedOnGpu && bc) {
                        success = TextureExportDetails::EncodeBC(mip, compression, quality, cutoff, m_pState->encoderThreads,
                            encoded.bytes, isCancelled, mipProgress);
                    }
                    else if (!encodedOnGpu && compression >= SR_GRAPH_NS::TextureCompression::ASTC4x4 && compression <= SR_GRAPH_NS::TextureCompression::ASTC8x8) {
                        const auto block = SR_GRAPH_NS::TextureContainer::GetBlockInfo(compression, format);
                        if (!m_pState->pAstc || m_pState->astcBlock != block.width
                            || !SR_EQUALS(m_pState->astcQuality, quality) || m_pState->astcSrgb != srgb) {
                            if (m_pState->pAstc) {
                                astcenc_context_free(m_pState->pAstc);
                                m_pState->pAstc = nullptr;
                            }
                            astcenc_config config{};
                            success = astcenc_config_init(srgb ? ASTCENC_PRF_LDR_SRGB : ASTCENC_PRF_LDR,
                                block.width, block.height, 1, quality * 100.f, 0, &config) == ASTCENC_SUCCESS;
                        #ifdef SR_ASTCENC_HAS_PARENT_CONTEXT
                            success = success && astcenc_context_alloc(&config, m_pState->encoderThreads, &m_pState->pAstc, nullptr) == ASTCENC_SUCCESS;
                        #else
                            success = success && astcenc_context_alloc(&config, m_pState->encoderThreads, &m_pState->pAstc) == ASTCENC_SUCCESS;
                        #endif
                            m_pState->astcBlock = block.width;
                            m_pState->astcQuality = quality;
                            m_pState->astcSrgb = srgb;
                            if (success) {
                                SR_INFO("TextureExporter::Prepare() : initialized ASTC CPU encoder with {} threads", m_pState->encoderThreads);
                            }
                        }
                        if (success) {
                            void* pSlice = const_cast<float_t*>(mip.pixels.data());
                            astcenc_image image { mip.width, mip.height, 1, ASTCENC_TYPE_F32, &pSlice };
                            const astcenc_swizzle swizzle { ASTCENC_SWZ_R, ASTCENC_SWZ_G, ASTCENC_SWZ_B, ASTCENC_SWZ_A };
                            std::atomic<bool> failed = false;
                            auto compress = [&](uint32_t threadIndex) {
                                SR_TRACY_ZONE_N("ASTC compression");
                                if (astcenc_compress_image(m_pState->pAstc, &image, &swizzle,
                                    encoded.bytes.data(), encoded.bytes.size(), threadIndex) != ASTCENC_SUCCESS) {
                                    failed = true;
                                }
                            };
                            SR_UTILS_NS::Vector<SR_HTYPES_NS::Thread*> threads;
                            const uint32_t threadCount = encoded.bytes.size() < 4096 ? 1
                                : static_cast<uint32_t>(std::min(uint64_t(m_pState->encoderThreads), encoded.bytes.size() / 16));
                            for (uint32_t threadIndex = 1; threadIndex < threadCount; ++threadIndex) {
                                SR_HTYPES_NS::Thread* pThread = nullptr;
                                SR_HTYPES_NS::Thread::Factory::Instance().Create(pThread, [&, threadIndex]() {
                                    compress(threadIndex);
                                    return false;
                                });
                                threads.emplace_back(pThread);
                            }
                            compress(0);
                            for (auto&& pThread : threads) {
                                pThread->Join();
                                pThread->Free();
                            }
                            const auto resetResult = astcenc_compress_reset(m_pState->pAstc);
                            success = !failed && resetResult == ASTCENC_SUCCESS;
                        }
                    }
                    else if (!encodedOnGpu) {
                        Etc::Image::Format etcFormat = Etc::Image::Format::UNKNOWN;
                        switch (compression) {
                            case SR_GRAPH_NS::TextureCompression::ETC2RGB: etcFormat = srgb ? Etc::Image::Format::SRGB8 : Etc::Image::Format::RGB8; break;
                            case SR_GRAPH_NS::TextureCompression::ETC2RGBA: etcFormat = srgb ? Etc::Image::Format::SRGBA8 : Etc::Image::Format::RGBA8; break;
                            case SR_GRAPH_NS::TextureCompression::EACR11: etcFormat = Etc::Image::Format::R11; break;
                            case SR_GRAPH_NS::TextureCompression::EACRG11: etcFormat = Etc::Image::Format::RG11; break;
                            default: break;
                        }
                        Etc::Image image(const_cast<float_t*>(mip.pixels.data()), mip.width, mip.height, Etc::ErrorMetric::NUMERIC);
                        const uint32_t threadCount = static_cast<uint32_t>(std::min(uint64_t(m_pState->encoderThreads),
                            ((uint64_t(mip.width) + 3) / 4) * ((uint64_t(mip.height) + 3) / 4)));
                        const auto result = image.Encode(etcFormat, Etc::ErrorMetric::NUMERIC, quality * 100.f, threadCount, threadCount);
                        success = result < Etc::Image::ERROR_THRESHOLD && image.GetEncodingBitsBytes() == encoded.bytes.size();
                        if (success) {
                            memcpy(encoded.bytes.data(), image.GetEncodingBits(), encoded.bytes.size());
                        }
                    }
                    if (isCancelled && isCancelled()) {
                        return false;
                    }
                    if (!success) {
                        SR_ERROR("TextureExporter::Prepare() : encoding failed for {}", variant);
                        return false;
                    }
                    if (compression == SR_GRAPH_NS::TextureCompression::BC1) {
                        TextureExportDetails::ApplyBC1Alpha(mip, cutoff, encoded.bytes);
                    }
                    mipProgress(1.f);
                    completedMipPixels += uint64_t(mip.width) * mip.height;
                }
                SR_UTILS_NS::String bytes;
                if (!TextureExportDetails::WriteKtx(texture, bytes)
                    || !SR_GRAPH_NS::TextureContainer::Read(SR_UTILS_NS::StringView(bytes), validated)) {
                    SR_ERROR("TextureExporter::Prepare() : invalid encoder result for {}", variant);
                    return false;
                }
                auto&& vfs = SR_UTILS_NS::VFS::Instance();
                outputHash = SR_GRAPH_NS::TextureContainer::HashBytes(bytes);
                if (receipt.IsFile()) {
                    vfs.Delete(receipt);
                }
                if (!vfs.WriteFileAtomic(output, bytes)
                    || (isCancelled && isCancelled())
                    || !vfs.WriteFileAtomic(receipt, "{}:{}"_format(hash, outputHash))) {
                    vfs.Delete(output);
                    vfs.Delete(receipt);
                    return false;
                }
                const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - started).count();
                SR_INFO("TextureExporter::Prepare() : {}: {} bytes -> {} bytes, {} ms, GPU mip levels {}/{}",
                    variant, sourceBytes.size(), bytes.size(), milliseconds, gpuMips, mips.size());
            }
            if (validateQuality && !qualityCached) {
                const auto qualityStarted = std::chrono::steady_clock::now();
                if (mips.size() != validated.mips.size()) {
                    return false;
                }
                if (compression == SR_GRAPH_NS::TextureCompression::BC7 && !m_pState->pBC7Decode) {
                    if (CreateOptionsBC7(&m_pState->pBC7Decode) != 0 || !m_pState->pBC7Decode) {
                        return false;
                    }
                }
                SR_UTILS_NS::Vector<float_t> decodedPixels;
                for (uint32_t level = 0; level < validated.mips.size(); ++level) {
                    if (isCancelled && isCancelled()) {
                        return false;
                    }
                    auto&& mip = validated.mips[level];
                    const bool decoded = TextureExportDetails::DecodeColor(mip, compression, format, mips[level], m_pState->pBC7Decode, decodedPixels);
                    const auto measured = decoded ? TextureQuality::Measure(mips[level].pixels, decodedPixels, mip.width, mip.height, policy) : TextureQualityResult();
                    qualityPassed &= measured.accepted;
                    reportVariantProgress(0.85f + 0.14f * static_cast<float_t>(level + 1) / validated.mips.size());
                    SR_INFO("TextureExporter::Prepare() : {} mip {}: color PSNR {}, alpha PSNR {}, block RMSE P99.9 {}, alpha error P99.9 {}, bad blocks {}%, bad alpha {}%, worst block {}, max alpha {}, {}",
                        variant, level, measured.colorPsnr, measured.alphaPsnr, measured.blockRmseP999, measured.alphaErrorP999,
                        measured.badBlockFraction * 100.f, measured.badAlphaFraction * 100.f, measured.worstBlockRmse,
                        measured.maxAlphaError, measured.accepted ? "quality passed" : "quality warning");
                }
                if (!SR_UTILS_NS::VFS::Instance().WriteFileAtomic(qualityReceipt, "{}:{}:{}:{}"_format(
                    SR_TEXTURE_QUALITY_REVISION, static_cast<uint32_t>(policy), outputHash, qualityPassed ? "passed" : "failed"))) {
                    return false;
                }
                const auto qualityMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - qualityStarted).count();
                SR_INFO("TextureExporter::Prepare() : quality validation for {}: {} ms; {} blocks",
                    variant, qualityMilliseconds, cached ? "reused cached" : "newly encoded");
            }
            reportVariantProgress(1.f);
            if (validateQuality && !qualityPassed) {
                if (metadata.qualityValidation == SR_GRAPH_NS::TextureQualityValidation::Strict) {
                    SR_WARN("TextureExporter::Prepare() : strict quality check rejected {}; using another variant or lossless fallback", variant);
                    continue;
                }
                SR_WARN("TextureExporter::Prepare() : quality warning for {}; keeping compressed texture in Warn mode", variant);
            }
            artifacts.emplace_back(TextureBuildArtifact{ variant, output });
            metadata.preparedVariants.emplace_back(variant);
            metadata.preparedHashes.emplace_back(outputHash);
            metadata.compressed |= compression != SR_GRAPH_NS::TextureCompression::None;
            desktopCompressedSelected |= profile == SR_GRAPH_NS::TextureExportProfile::Desktop && compression != SR_GRAPH_NS::TextureCompression::None;
        }
        return true;
    #endif
    }
}
