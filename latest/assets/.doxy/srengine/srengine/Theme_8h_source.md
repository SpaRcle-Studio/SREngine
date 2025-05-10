

# File Theme.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**Editor**](dir_ee39d7974ea8a860c3bbba1b251e09d1.md) **>** [**Theme.h**](Theme_8h.md)

[Go to the documentation of this file](Theme_8h.md)


```C++
//
// Created by Monika on 02.03.2022.
//

#ifndef SR_ENGINE_GRAPHICS_THEME_H
#define SR_ENGINE_GRAPHICS_THEME_H

#include <Utils/Math/Vector4.h>

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
```


