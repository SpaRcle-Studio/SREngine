//
// Created by Monika on 22.07.2022.
//

#ifndef SRENGINE_GROUPPASS_H
#define SRENGINE_GROUPPASS_H

#include <Graphics/Pass/BasePass.h>

namespace SR_GRAPH_NS {
    class GroupPass : public BasePass {
    public:
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

        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnSamplesChanged() override;

        void SetRenderTechnique(RenderTechnique* pRenderTechnique) override;

        SR_NODISCARD BasePass* FindPass(const SR_UTILS_NS::StringAtom& name) const;

        bool ForEachPass(const SR_HTYPES_NS::Function<bool(BasePass*)>& callback) const;

        template<typename T> SR_NODISCARD T* FindPass() const;

        void SR_FASTCALL OnMeshAdded(SR_GTYPES_NS::Mesh* pMesh, bool transparent) override;
        void SR_FASTCALL OnMeshRemoved(SR_GTYPES_NS::Mesh* pMesh, bool transparent) override;

    protected:
        std::vector<BasePass*> m_passes;

    };

    template<typename T> T* GroupPass::FindPass() const {
        for (auto&& pPass : m_passes) {
            if (auto&& pFoundPass = dynamic_cast<T*>(pPass)) {
                return pFoundPass;
            }

            if (auto&& pGroupPass = dynamic_cast<GroupPass*>(pPass)) {
                if (auto&& pFoundPass = pGroupPass->FindPass<T>()) {
                    return pFoundPass;
                }
            }
        }

        return nullptr;
    }
}

#endif //SRENGINE_GROUPPASS_H
