

# File AtlasBuilder.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Utils**](dir_1d6f88bd3f47a17aa2fb3667e19494af.md) **>** [**AtlasBuilder.h**](AtlasBuilder_8h.md)

[Go to the documentation of this file](AtlasBuilder_8h.md)


```C++
//
// Created by qulop on 17.03.2024
//
#ifndef SR_ENGINE_ATLAS_BUILDER_H
#define SR_ENGINE_ATLAS_BUILDER_H

#include <Graphics/macros.h>

#include <Utils/stdInclude.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Math/Vector2.h>
#include <Graphics/Loaders/TextureLoader.h>

namespace SR_GRAPH_NS {
    struct AtlasBuilderData {
        SR_UTILS_NS::Path source;
        SR_UTILS_NS::Path destination;
        std::string extension = "png";
        bool saveInCache = false;
        SR_MATH_NS::UVector2 quantityOnAxes;
        SR_MATH_NS::UVector2 step;
    };

    class AtlasBuilder : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        AtlasBuilder(AtlasBuilderData data);

    public:
        SR_NODISCARD bool Generate();

        SR_NODISCARD bool Save() const;
        SR_NODISCARD bool SaveConfig(const SR_UTILS_NS::Path& path) const;

    public:
        SR_NODISCARD SR_UTILS_NS::Path GetLocation() const { return m_data.source; }
        SR_NODISCARD bool IsInCache() const { return m_data.saveInCache; }
        SR_NODISCARD SR_MATH_NS::UVector2 GetQuantity() const { return m_data.quantityOnAxes; }
        SR_NODISCARD SR_MATH_NS::UVector2 GetStep() const { return m_data.step; }

    private:
        SR_NODISCARD bool Create();
        SR_NODISCARD bool CreateLinearAtlas();;

    private:
        AtlasBuilderData m_data;
        SR_MATH_NS::UVector2 m_totalSize;

        std::vector<SR_GRAPH_NS::TextureData::Ptr> m_sprites;
        SR_GRAPH_NS::TextureData::Ptr m_atlas;
    };

}
#endif // SR_ENGINE_ATLAS_BUILDER_H
```


