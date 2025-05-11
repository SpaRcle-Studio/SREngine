

# File BasePass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**BasePass.h**](BasePass_8h.md)

[Go to the documentation of this file](BasePass_8h.md)


```C++
//
// Created by Monika on 14.07.2022.
//

#ifndef SR_ENGINE_BASE_PASS_H
#define SR_ENGINE_BASE_PASS_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/Time.h>
#include <Utils/Resources/Xml.h>
#include <Utils/Resources/ResourceContainer.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/SRLM/Utils.h>

#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Memory/DescriptorManager.h>

namespace SR_GTYPES_NS {
    class Camera;
    class Mesh;
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
    class RenderTechnique;
    class IRenderTechnique;
    class Pipeline;
    class BasePass;

    typedef std::map<std::string, SR_HTYPES_NS::Function<BasePass*(const SR_XML_NS::Node&, IRenderTechnique*)>> RenderPassMap;
    RenderPassMap& GetRenderPassMap();

    class BasePass : public SR_UTILS_NS::ResourceContainer, public SR_SRLM_NS::IExecutableNode {
        using Super = SR_UTILS_NS::ResourceContainer;
    public:
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using Context = RenderContext*;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
    public:
        BasePass();
        ~BasePass() override = default;

    public:
        virtual bool Load(const SR_XML_NS::Node& passNode);

        virtual bool Init();
        virtual void DeInit();

        virtual bool HasPreRender() const noexcept { return true; }
        virtual bool HasRender() const noexcept { return true; }
        virtual bool HasPostRender() const noexcept { return true; }
        virtual bool HasUpdate() const noexcept { return true; }

        virtual bool Overlay() { return false; }

        virtual void Bind() { }

        virtual void Prepare() { }

        virtual bool PreRender() { return false; }
        virtual bool Render() { return false; }
        virtual bool PostRender() { return false; }

        virtual void Update() { }
        virtual void PostUpdate() { }

        virtual void OnResize(const SR_MATH_NS::UVector2& size) { }
        virtual void OnMultisampleChanged() { }

        virtual void SR_FASTCALL OnMeshAdded(SR_GTYPES_NS::Mesh* pMesh, bool transparent) { }
        virtual void SR_FASTCALL OnMeshRemoved(SR_GTYPES_NS::Mesh* pMesh, bool transparent) { }

        SR_NODISCARD virtual std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const { return { }; }

        virtual void SetRenderTechnique(IRenderTechnique* pRenderTechnique);
        void SetName(SR_UTILS_NS::StringAtom name);
        void SetContext(Context pContext);
        void SetParent(BasePass* pParent) { m_parent = pParent; }

        SR_NODISCARD virtual RenderScenePtr GetRenderScene() const;
        SR_NODISCARD Context GetContext() const { return m_context; }
        SR_NODISCARD PipelinePtr GetPassPipeline() const { return m_pipeline; }
        SR_NODISCARD IRenderTechnique* GetTechnique() const { return m_technique; }
        SR_NODISCARD bool IsInit() const { return m_isInit; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const;
        SR_NODISCARD BasePass* GetParent() const { return m_parent; }

    protected:
        CameraPtr m_camera = nullptr;
        Memory::UBOManager& m_uboManager;
        DescriptorManager& m_descriptorManager;

    private:
        BasePass* m_parent = nullptr;

        Context m_context = nullptr;
        PipelinePtr m_pipeline = nullptr;

        SR_UTILS_NS::StringAtom m_name;

        IRenderTechnique* m_technique = nullptr;
        bool m_isInit = false;

    };

    class StartPassNode : public SR_SRLM_NS::IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(StartPassNode, Start Pass, { "Passes" })
    public:
        void InitNode() override;

    };
}

#define SR_REGISTER_RENDER_PASS(name)                                                                                   \
    static bool SR_CODEGEN_##name##_render_pass_register_result =                                                       \
        SR_GRAPH_NS::GetRenderPassMap().insert(std::make_pair(                                                          \
            std::move(#name),                                                                                           \
            [](const SR_XML_NS::Node& node, IRenderTechnique* pTechnique) -> SR_GRAPH_NS::BasePass* {                   \
                BasePass* pPass = new name();                                                                           \
                pPass->SetRenderTechnique(pTechnique);                                                                  \
                if (!pPass->Load(node)) {                                                                               \
                    delete pPass;                                                                                       \
                    pPass = nullptr;                                                                                    \
                }                                                                                                       \
                return pPass;                                                                                           \
            }                                                                                                           \
        )).second;                                                                                                      \

#define SR_ALLOCATE_RENDER_PASS(passNode, pTechnique)                                                                   \
    (SR_GRAPH_NS::GetRenderPassMap().count(passNode.Name()) == 0 ? nullptr :                                            \
        SR_GRAPH_NS::GetRenderPassMap().at(passNode.Name())(passNode, pTechnique))                                      \


#endif //SR_ENGINE_BASE_PASS_H
```


