//
// Created by Monika on 28.11.2026.
//

#include <Engine/GUI/GameBuildIcon.h>

#include <Graphics/Loaders/TextureLoader.h>

#include <Utils/FileSystem/FileSystem.h>

namespace SR_CORE_GUI_NS {
    bool GameBuildIcon::Load(const SR_UTILS_NS::Path& path) {
        SR_TRACY_ZONE;
        Clear();

        SR_UTILS_NS::String bytes;
        if (!SR_UTILS_NS::FileSystem::ReadFile(path, bytes)) {
            SR_ERROR("GameBuildIcon::Load() : failed to read icon!\n\tPath: {}", path);
            return false;
        }

        SR_GRAPH_NS::TextureSourceInfo info;
        if (!SR_GRAPH_NS::TextureLoader::DecodeSource(bytes, info, m_pixels) || info.width == 0 || info.height == 0) {
            SR_ERROR("GameBuildIcon::Load() : failed to decode icon!\n\tPath: {}", path);
            Clear();
            return false;
        }

        m_width = info.width;
        m_height = info.height;

        /// HDR sources are already linear.
        if (!info.hdr) {
            for (SR_UTILS_NS::SizeType i = 0; i < m_pixels.size(); i += 4) {
                for (SR_UTILS_NS::SizeType channel = 0; channel < 3; ++channel) {
                    m_pixels[i + channel] = static_cast<float_t>(SrgbToLinear(m_pixels[i + channel]));
                }
            }
        }

        return true;
    }

    double_t GameBuildIcon::SrgbToLinear(double_t value) {
        value = std::clamp(value, 0.0, 1.0);
        return value <= 0.04045 ? value / 12.92 : std::pow((value + 0.055) / 1.055, 2.4);
    }

    double_t GameBuildIcon::LinearToSrgb(double_t value) {
        value = std::clamp(value, 0.0, 1.0);
        return value <= 0.0031308 ? value * 12.92 : 1.055 * std::pow(value, 1.0 / 2.4) - 0.055;
    }

    void GameBuildIcon::Clear() {
        m_pixels.clear();
        m_width = 0;
        m_height = 0;
    }

    void GameBuildIcon::Append16(SR_UTILS_NS::String& data, uint16_t value) {
        data += static_cast<char>(value & 0xFF);
        data += static_cast<char>(value >> 8);
    }

    void GameBuildIcon::Append32(SR_UTILS_NS::String& data, uint32_t value) {
        Append16(data, static_cast<uint16_t>(value & 0xFFFF));
        Append16(data, static_cast<uint16_t>(value >> 16));
    }

    void GameBuildIcon::Resample(uint32_t width, uint32_t height, SR_UTILS_NS::Vector<uint8_t>& rgba) const {
        SR_TRACY_ZONE;
        rgba.clear();
        rgba.resize(static_cast<SR_UTILS_NS::SizeType>(width) * height * 4, 0);
        if (!IsValid() || width == 0 || height == 0) {
            return;
        }

        /// The image keeps its aspect ratio and is centered on a transparent canvas.
        const double_t scale = std::min(static_cast<double_t>(width) / m_width, static_cast<double_t>(height) / m_height);
        const double_t left = (width - m_width * scale) * 0.5;
        const double_t top = (height - m_height * scale) * 0.5;
        const double_t footprint = 1.0 / scale;

        std::array<double_t, 3> color = {};
        double_t alpha = 0.0;

        auto&& accumulate = [&](uint32_t sourceX, uint32_t sourceY, double_t weight) {
            const auto source = (static_cast<SR_UTILS_NS::SizeType>(sourceY) * m_width + sourceX) * 4;
            const double_t sourceAlpha = std::clamp(static_cast<double_t>(m_pixels[source + 3]), 0.0, 1.0) * weight;
            for (uint32_t channel = 0; channel < 3; ++channel) {
                color[channel] += std::clamp(static_cast<double_t>(m_pixels[source + channel]), 0.0, 1.0) * sourceAlpha;
            }
            alpha += sourceAlpha;
        };

        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {
                color = {};
                alpha = 0.0;

                if (scale >= 1.0) {
                    /// Upscaling: bilinear filtering inside the image area.
                    const double_t sourceX = (x + 0.5 - left) / scale;
                    const double_t sourceY = (y + 0.5 - top) / scale;
                    if (sourceX < 0.0 || sourceY < 0.0 || sourceX >= m_width || sourceY >= m_height) {
                        continue;
                    }

                    const double_t filterX = std::clamp(sourceX - 0.5, 0.0, m_width - 1.0);
                    const double_t filterY = std::clamp(sourceY - 0.5, 0.0, m_height - 1.0);
                    const uint32_t x0 = static_cast<uint32_t>(filterX);
                    const uint32_t y0 = static_cast<uint32_t>(filterY);
                    const uint32_t x1 = std::min(x0 + 1, m_width - 1);
                    const uint32_t y1 = std::min(y0 + 1, m_height - 1);
                    const double_t tx = filterX - x0;
                    const double_t ty = filterY - y0;

                    accumulate(x0, y0, (1.0 - tx) * (1.0 - ty));
                    accumulate(x1, y0, tx * (1.0 - ty));
                    accumulate(x0, y1, (1.0 - tx) * ty);
                    accumulate(x1, y1, tx * ty);
                }
                else {
                    /// Downscaling: area averaging of all covered source pixels.
                    const double_t sourceLeft = (x - left) * footprint;
                    const double_t sourceTop = (y - top) * footprint;
                    const double_t sourceRight = sourceLeft + footprint;
                    const double_t sourceBottom = sourceTop + footprint;

                    const uint32_t beginX = static_cast<uint32_t>(std::max(0.0, std::floor(sourceLeft)));
                    const uint32_t beginY = static_cast<uint32_t>(std::max(0.0, std::floor(sourceTop)));
                    const uint32_t endX = static_cast<uint32_t>(std::min(static_cast<double_t>(m_width), std::ceil(sourceRight)));
                    const uint32_t endY = static_cast<uint32_t>(std::min(static_cast<double_t>(m_height), std::ceil(sourceBottom)));
                    const double_t area = footprint * footprint;

                    for (uint32_t sourceY = beginY; sourceY < endY; ++sourceY) {
                        const double_t weightY = std::min(sourceY + 1.0, sourceBottom) - std::max(static_cast<double_t>(sourceY), sourceTop);
                        for (uint32_t sourceX = beginX; sourceX < endX; ++sourceX) {
                            const double_t weightX = std::min(sourceX + 1.0, sourceRight) - std::max(static_cast<double_t>(sourceX), sourceLeft);
                            if (weightX > 0.0 && weightY > 0.0) {
                                accumulate(sourceX, sourceY, weightX * weightY / area);
                            }
                        }
                    }
                }

                if (alpha <= 0.0) {
                    continue;
                }

                const auto index = (static_cast<SR_UTILS_NS::SizeType>(y) * width + x) * 4;
                for (uint32_t channel = 0; channel < 3; ++channel) {
                    rgba[index + channel] = static_cast<uint8_t>(LinearToSrgb(color[channel] / alpha) * 255.0 + 0.5);
                }
                rgba[index + 3] = static_cast<uint8_t>(std::clamp(alpha, 0.0, 1.0) * 255.0 + 0.5);
            }
        }
    }

    SR_UTILS_NS::String GameBuildIcon::EncodePng(uint32_t width, uint32_t height) const {
        SR_TRACY_ZONE;
        SR_UTILS_NS::Vector<uint8_t> rgba;
        Resample(width, height, rgba);
        return SR_GRAPH_NS::TextureLoader::EncodeRgbaPng(rgba.data(), width, height);
    }

    SR_UTILS_NS::String GameBuildIcon::EncodeBitmap(uint32_t size) const {
        SR_UTILS_NS::Vector<uint8_t> rgba;
        Resample(size, size, rgba);

        const uint32_t maskStride = ((size + 31) / 32) * 4;
        const uint32_t pixelBytes = size * size * 4;
        const uint32_t maskBytes = maskStride * size;

        SR_UTILS_NS::String result;
        result.reserve(40 + pixelBytes + maskBytes);

        /// BITMAPINFOHEADER, the height includes the AND mask.
        Append32(result, 40);
        Append32(result, size);
        Append32(result, size * 2);
        Append16(result, 1);
        Append16(result, 32);
        Append32(result, 0);
        Append32(result, pixelBytes + maskBytes);
        Append32(result, 0);
        Append32(result, 0);
        Append32(result, 0);
        Append32(result, 0);

        /// Bitmap rows are stored bottom-up in BGRA order.
        for (uint32_t row = size; row > 0; --row) {
            const auto rowOffset = static_cast<SR_UTILS_NS::SizeType>(row - 1) * size * 4;
            for (uint32_t x = 0; x < size; ++x) {
                const auto index = rowOffset + x * 4;
                result += static_cast<char>(rgba[index + 2]);
                result += static_cast<char>(rgba[index + 1]);
                result += static_cast<char>(rgba[index + 0]);
                result += static_cast<char>(rgba[index + 3]);
            }
        }

        SR_UTILS_NS::String maskRow;
        for (uint32_t row = size; row > 0; --row) {
            maskRow.clear();
            maskRow.resize(maskStride, '\0');
            const auto rowOffset = static_cast<SR_UTILS_NS::SizeType>(row - 1) * size * 4;
            for (uint32_t x = 0; x < size; ++x) {
                if (rgba[rowOffset + x * 4 + 3] == 0) {
                    maskRow[x / 8] = static_cast<char>(static_cast<uint8_t>(maskRow[x / 8]) | (0x80 >> (x % 8)));
                }
            }
            result += maskRow;
        }

        return result;
    }

    SR_UTILS_NS::String GameBuildIcon::EncodeIco() const {
        SR_TRACY_ZONE;
        /// Intermediate sizes cover display scaling, otherwise the shell resamples the nearest image itself.
        static constexpr std::array<uint32_t, 12> sizes = { 16, 20, 24, 32, 40, 48, 64, 72, 96, 128, 192, 256 };

        if (!IsValid()) {
            return SR_UTILS_NS::String();
        }

        /// Large images are stored as PNG, small ones as bitmaps for compatibility with old shell code.
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> images;
        images.reserve(sizes.size());
        for (const uint32_t size : sizes) {
            auto&& image = images.emplace_back(size >= 256 ? EncodePng(size, size) : EncodeBitmap(size));
            if (image.empty()) {
                return SR_UTILS_NS::String();
            }
        }

        SR_UTILS_NS::String result;
        Append16(result, 0);
        Append16(result, 1);
        Append16(result, static_cast<uint16_t>(sizes.size()));

        uint32_t offset = static_cast<uint32_t>(6 + 16 * sizes.size());
        for (uint32_t i = 0; i < sizes.size(); ++i) {
            const char dimension = static_cast<char>(sizes[i] >= 256 ? 0 : sizes[i]);
            result += dimension;
            result += dimension;
            result += '\0';
            result += '\0';
            Append16(result, 1);
            Append16(result, 32);
            Append32(result, static_cast<uint32_t>(images[i].size()));
            Append32(result, offset);
            offset += static_cast<uint32_t>(images[i].size());
        }

        for (auto&& image : images) {
            result += image;
        }

        return result;
    }
}
