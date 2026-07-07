//
// Created by Monika on 02.03.2022.
//

#ifndef SR_ENGINE_GRAPHICS_THEME_H
#define SR_ENGINE_GRAPHICS_THEME_H

#include <ImmediateGUI/stdInclude.h>

#include <Utils/Math/Vector4.h>

namespace SR_UTILS_NS {
    class Path;
}

namespace SR_GRAPH_GUI_NS {
    class Theme : public SR_UTILS_NS::NonCopyable {
    public:
        ~Theme() override = default;

    public:
        static Theme* Load(const SR_UTILS_NS::Path& path);
        static bool SaveGlobal(const SR_UTILS_NS::Path& path);

    public:
        bool Save(const SR_UTILS_NS::Path& path);

        bool Apply() const;

        void SetColor(const std::string& id, const SR_MATH_NS::FColor& color);
        void SetSize(const std::string& id, const SR_MATH_NS::FVector2& size);
        void SetFloat(const std::string& id, float_t value);
        void SetBool(const std::string& id, bool value);

    private:
        std::unordered_map<std::string, SR_MATH_NS::FColor> m_colors;
        std::unordered_map<std::string, SR_MATH_NS::FVector2> m_sizes;
        std::unordered_map<std::string, float_t> m_floats;
        std::unordered_map<std::string, float_t> m_booleans;

    };
}

#endif //SR_ENGINE_GRAPHICS_THEME_H
