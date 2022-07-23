//
// Created by Monika on 22.07.2022.
//

#ifndef SRENGINE_GROUPPASS_H
#define SRENGINE_GROUPPASS_H

#include <Pass/BasePass.h>

namespace SR_GRAPH_NS {
    class GroupPass : public BasePass {
    public:
        explicit GroupPass(RenderTechnique* pTechnique);
        ~GroupPass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        bool Init() override;
        void DeInit() override;

        void PreRender() override;
        void Render() override;
        void PostRender() override;

        void Update() override;
        void Overlay() override;

        void OnResize(const SR_MATH_NS::IVector2& size) override;

    private:
        std::list<BasePass*> m_passes;

    };
}

#endif //SRENGINE_GROUPPASS_H
