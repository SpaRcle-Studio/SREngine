//
// Created by innerviewer on 1/6/2024.
//

#ifndef SRENGINE_LAYERMANAGER_H
#define SRENGINE_LAYERMANAGER_H

#include <Utils/Settings.h>

namespace SR_UTILS_NS {
    class LayerManager : public GlobalSettings<LayerManager> {
        SR_REGISTER_SINGLETON(LayerManager);
        friend class GlobalSettings<LayerManager>;
        using Super = GlobalSettings<LayerManager>;

    public:
        //SR_NODISCARD const std::string& GetLayer(Layer layer) const;
        //SR_NODISCARD const std::string& GetLayerByIndex(uint16_t index) const;
        SR_NODISCARD uint16_t GetLayerIndex(StringAtom layer) const;
        SR_NODISCARD std::vector<StringAtom> GetLayers() const { return m_layers; }
        SR_NODISCARD StringAtom GetDefaultLayer() const noexcept { return m_defaultLayer; }

        //SR_NODISCARD Hash HashTag(const std::string& tag) const;

    protected:
        SR_NODISCARD SR_UTILS_NS::Path InitializeResourcePath() const override;

        void ClearSettings() override;
        bool LoadSettings(const SR_XML_NS::Node& node) override;

        //Hash RegisterTag(const std::string& tag);

    private:
        //std::map<Hash, std::string> m_layerNames;
        //std::map<Hash, uint16_t> m_indices;
        std::vector<StringAtom> m_layers;
        StringAtom m_defaultLayer;

    };
}
#endif //SRENGINE_LAYERMANAGER_H
