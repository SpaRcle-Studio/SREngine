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

        bool Overlay() override;

        void Prepare() override;

        bool PreRender() override;
        bool Render() override;
        bool PostRender() override;

        void Update() override;

        void OnResize(const SR_MATH_NS::IVector2& size) override;

        SR_NODISCARD BasePass* FindPass(const std::string& name) const;

        void SR_FASTCALL OnMeshAdded(SR_GTYPES_NS::Mesh* pMesh, bool transparent) override;
        void SR_FASTCALL OnMeshRemoved(SR_GTYPES_NS::Mesh* pMesh, bool transparent) override;

    protected:
        std::list<BasePass*> m_passes;

    };
}

#endif //SRENGINE_GROUPPASS_H
