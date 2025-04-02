

# File LayerManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**LayerManager.h**](LayerManager_8h.md)

[Go to the documentation of this file](LayerManager_8h.md)


```C++
//
// Created by innerviewer on 1/6/2024.
//

#ifndef SR_ENGINE_LAYER_MANAGER_H
#define SR_ENGINE_LAYER_MANAGER_H

#include <Utils/Settings.h>

namespace SR_UTILS_NS {
    class LayerManager : public GlobalSettings<LayerManager> {
        SR_REGISTER_SINGLETON(LayerManager);
        friend class GlobalSettings<LayerManager>;
        using Super = GlobalSettings<LayerManager>;

    public:
        SR_NODISCARD bool HasLayer(StringAtom layer) const;
        SR_NODISCARD uint16_t GetLayerIndex(StringAtom layer) const;
        SR_NODISCARD std::vector<StringAtom> GetLayers() const { return m_layers; }

        SR_NODISCARD static StringAtom GetDefaultLayer();

        SR_NODISCARD uint64_t GetHashState() const { return m_hashState; }

    protected:
        SR_NODISCARD SR_UTILS_NS::Path InitializeResourcePath() const override;

        void ClearSettings() override;
        bool LoadSettings(const SR_XML_NS::Node& node) override;

    private:
        std::vector<StringAtom> m_layers;
        std::atomic<StringAtom> m_defaultLayer;
        uint64_t m_hashState = 0;

    };
}
#endif //SR_ENGINE_LAYERMANAGER_H
```


