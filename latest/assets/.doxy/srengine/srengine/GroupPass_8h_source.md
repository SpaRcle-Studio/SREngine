

# File GroupPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**GroupPass.h**](GroupPass_8h.md)

[Go to the documentation of this file](GroupPass_8h.md)


```C++
//
// Created by Monika on 22.07.2022.
//

#ifndef SR_ENGINE_GROUPPASS_H
#define SR_ENGINE_GROUPPASS_H

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
        void PostUpdate() override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnMultisampleChanged() override;

        void SetRenderTechnique(IRenderTechnique* pRenderTechnique) override;

        SR_NODISCARD BasePass* FindPass(const SR_UTILS_NS::StringAtom& name) const;

        bool ForEachPass(const SR_HTYPES_NS::Function<bool(BasePass*)>& callback) const;

        template<typename T> SR_NODISCARD T* FindPass() const;

        void SR_FASTCALL OnMeshAdded(SR_GTYPES_NS::Mesh* pMesh, bool transparent) override;
        void SR_FASTCALL OnMeshRemoved(SR_GTYPES_NS::Mesh* pMesh, bool transparent) override;

    protected:
        std::vector<BasePass::Ptr> m_passes;

    };

    template<typename T> T* GroupPass::FindPass() const {
        for (auto&& pPass : m_passes) {
            if (auto&& pFoundPass = pPass.DynamicCast<T>()) {
                return const_cast<T*>(pFoundPass.Get());
            }

            if (auto&& pGroupPass = pPass.DynamicCast<GroupPass>()) {
                if (auto&& pFoundPass = pGroupPass->FindPass<T>()) {
                    return pFoundPass;
                }
            }
        }

        return nullptr;
    }
}

#endif //SR_ENGINE_GROUPPASS_H
```


