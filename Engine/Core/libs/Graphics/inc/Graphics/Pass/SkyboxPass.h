//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_SKYBOXPASS_H
#define SRENGINE_SKYBOXPASS_H

#include <Graphics/Pass/BasePass.h>

namespace SR_GTYPES_NS {
    class Skybox;
}

namespace SR_GRAPH_NS {
    class SkyboxPass : public BasePass {
    public:
        explicit SkyboxPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~SkyboxPass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Render() override;
        void Update() override;
        bool Init() override;

    private:
        SR_GTYPES_NS::Skybox* m_skybox = nullptr;

    };
}

#endif //SRENGINE_SKYBOXPASS_H
