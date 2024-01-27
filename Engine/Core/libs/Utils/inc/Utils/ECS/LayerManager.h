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
        SR_NODISCARD StringAtom GetDefaultLayer() const noexcept { return m_defaultLayer; }

    protected:
        SR_NODISCARD SR_UTILS_NS::Path InitializeResourcePath() const override;

        void ClearSettings() override;
        bool LoadSettings(const SR_XML_NS::Node& node) override;

    private:
        std::vector<StringAtom> m_layers;
        StringAtom m_defaultLayer;

    };
}
#endif //SR_ENGINE_LAYERMANAGER_H
