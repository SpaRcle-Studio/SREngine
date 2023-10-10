//
// Created by Monika on 17.07.2022.
//

#ifndef SRENGINE_RENDERTECHNIQUE_H
#define SRENGINE_RENDERTECHNIQUE_H

#include <Graphics/Render/IRenderTechnique.h>

namespace SR_GRAPH_NS {
    /** Частично является настройкой, но может иметь множество экземпляров */
    class RenderTechnique : public SR_UTILS_NS::Settings, public IRenderTechnique {
    private:
        RenderTechnique() = default;

    public:
        static RenderTechnique* Load(const SR_UTILS_NS::Path& path);

    protected:
        bool Build() override;

        bool Load() override;
        bool Unload() override;

        bool LoadSettings(const SR_XML_NS::Node &node) override;
        void ClearSettings() override;

    };
}

#endif //SRENGINE_RENDERTECHNIQUE_H
