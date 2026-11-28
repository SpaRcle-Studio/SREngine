//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_GAME_BUILD_ICON_H
#define SR_ENGINE_GAME_BUILD_ICON_H

#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Vector.h>

namespace SR_CORE_GUI_NS {
    /// Source image of the game icon, scaled to the sizes required by the platforms.
    class GameBuildIcon {
    public:
        bool Load(const SR_UTILS_NS::Path& path);
        void Clear();

        SR_NODISCARD bool IsValid() const { return m_width > 0 && m_height > 0; }
        SR_NODISCARD SR_UTILS_NS::String EncodePng(uint32_t width, uint32_t height) const;
        SR_NODISCARD SR_UTILS_NS::String EncodeIco() const;

    private:
        void Resample(uint32_t width, uint32_t height, SR_UTILS_NS::Vector<uint8_t>& rgba) const;
        SR_NODISCARD SR_UTILS_NS::String EncodeBitmap(uint32_t size) const;

        static double_t SrgbToLinear(double_t value);
        static double_t LinearToSrgb(double_t value);
        static void Append16(SR_UTILS_NS::String& data, uint16_t value);
        static void Append32(SR_UTILS_NS::String& data, uint32_t value);

    private:
        /// Linear light RGBA, so downscaling keeps thin bright details.
        SR_UTILS_NS::Vector<float_t> m_pixels;
        uint32_t m_width = 0;
        uint32_t m_height = 0;

    };
}

#endif //SR_ENGINE_GAME_BUILD_ICON_H
