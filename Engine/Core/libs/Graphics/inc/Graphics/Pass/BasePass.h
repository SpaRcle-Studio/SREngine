//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_BASEPASS_H
#define SRENGINE_BASEPASS_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/Time.h>
#include <Utils/Xml.h>
#include <Utils/ResourceManager/ResourceContainer.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/SRLM/Utils.h>

#include <Graphics/Memory/UBOManager.h>

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
    class Pipeline;
    class BasePass;

    typedef std::map<std::string, SR_HTYPES_NS::Function<BasePass*(const SR_XML_NS::Node&)>> RenderPassMap;
    RenderPassMap& GetRenderPassMap();

    class BasePass : public SR_UTILS_NS::ResourceContainer, public SR_SRLM_NS::IExecutableNode {
    public:
        using Super = SR_UTILS_NS::ResourceContainer;
        using CameraPtr = Types::Camera*;
        using Context = RenderContext*;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
    public:
        BasePass();
        ~BasePass() override = default;

    public:
        virtual bool Load(const SR_XML_NS::Node& passNode);

        virtual bool Init();
        virtual void DeInit();

        /// Вызывается всегда и в самом начале
        virtual bool Overlay() { return false; }

        /// Вызывается всегда но полсе оверлея
        virtual void Prepare() { }

        /// Вызывается только во время построения
        virtual bool PreRender() { return false; }
        /// Вызывается только во время построения
        virtual bool Render() { return false; }
        /// Вызывается только во время построения
        virtual bool PostRender() { return false; }

        /// Вызывается постоянно после построения
        virtual void Update() { }

        virtual void OnResize(const SR_MATH_NS::UVector2& size) { }
        virtual void OnSamplesChanged() { }

        virtual void SR_FASTCALL OnMeshAdded(SR_GTYPES_NS::Mesh* pMesh, bool transparent) { }
        virtual void SR_FASTCALL OnMeshRemoved(SR_GTYPES_NS::Mesh* pMesh, bool transparent) { }

        SR_NODISCARD virtual std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const { return { }; }

        virtual void SetRenderTechnique(RenderTechnique* pRenderTechnique);
        void SetName(const std::string& name);

        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD Context GetContext() const { return m_context; }
        SR_NODISCARD PipelinePtr GetPipeline() const { return m_pipeline; }
        SR_NODISCARD RenderTechnique* GetTechnique() const { return m_technique; }
        SR_NODISCARD bool IsInit() const { return m_isInit; }
        SR_NODISCARD std::string_view GetName() const;
        SR_NODISCARD uint64_t GetHashName() const noexcept { return m_hashName; }

    protected:
        CameraPtr m_camera = nullptr;
        Context m_context = nullptr;
        PipelinePtr m_pipeline = nullptr;
        Memory::UBOManager& m_uboManager;

    private:
        std::string m_name;
        uint64_t m_hashName = 0;

        RenderTechnique* m_technique = nullptr;
        bool m_isInit = false;

    };

    class StartPassNode : public SR_SRLM_NS::IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(StartPassNode, Start Pass, { "Passes" })
    public:
        void InitNode() override;

    };
}

/// TODO: переделать на встраивание в объявление класса
#define SR_REGISTER_RENDER_PASS(name)                                                                                   \
    static bool SR_CODEGEN_##name##_render_pass_register_result =                                                       \
        SR_GRAPH_NS::GetRenderPassMap().insert(std::make_pair(                                                          \
            std::move(#name),                                                                                           \
            [](const SR_XML_NS::Node& node) -> SR_GRAPH_NS::BasePass* {                                                 \
                BasePass* pPass = new name();                                                                           \
                if (!pPass->Load(node)) {                                                                               \
                    delete pPass;                                                                                       \
                    pPass = nullptr;                                                                                    \
                }                                                                                                       \
                return pPass;                                                                                           \
            }                                                                                                           \
        )).second;                                                                                                      \

#define SR_ALLOCATE_RENDER_PASS(passNode)                                                                               \
    (SR_GRAPH_NS::GetRenderPassMap().count(passNode.Name()) == 0 ? nullptr :                                            \
        SR_GRAPH_NS::GetRenderPassMap().at(passNode.Name())(passNode))                                                  \


#endif //SRENGINE_BASEPASS_H
