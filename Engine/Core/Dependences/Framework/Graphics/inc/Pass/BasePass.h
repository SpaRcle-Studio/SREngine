//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_BASEPASS_H
#define SRENGINE_BASEPASS_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Xml.h>
#include <Memory/UBOManager.h>

namespace SR_GTYPES_NS {
    class Camera;
    class Mesh;
    class Shader;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderTechnique;
    class Environment;
    class BasePass;

    typedef std::map<std::string, std::function<BasePass*(RenderTechnique*, const SR_XML_NS::Node&)>> RenderPassMap;
    RenderPassMap& GetRenderPassMap();

    class BasePass : public SR_UTILS_NS::NonCopyable {
        using CameraPtr = Types::Camera*;
        using Context = RenderContext*;
        using PipelinePtr = Environment*;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
    public:
        explicit BasePass(RenderTechnique* pTechnique);
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

        virtual void OnResize(const SR_MATH_NS::IVector2& size) { }

        virtual void SR_FASTCALL OnMeshAdded(SR_GTYPES_NS::Mesh* pMesh, bool transparent) { }
        virtual void SR_FASTCALL OnMeshRemoved(SR_GTYPES_NS::Mesh* pMesh, bool transparent) { }

        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD Context GetContext() const { return m_context; }
        SR_NODISCARD PipelinePtr GetPipeline() const { return m_pipeline; }
        SR_NODISCARD RenderTechnique* GetTechnique() const { return m_technique; }
        SR_NODISCARD bool IsInit() const { return m_isInit; }

    protected:
        CameraPtr m_camera;
        Context m_context;
        PipelinePtr m_pipeline;
        Memory::UBOManager& m_uboManager;

    private:
        std::string m_name;
        RenderTechnique* m_technique;
        bool m_isInit;

    };
}

#define SR_REGISTER_RENDER_PASS(name)                                                                \
    static bool SR_CODEGEN_##name##_render_pass_register_result =                                    \
        SR_GRAPH_NS::GetRenderPassMap().insert(std::make_pair(                                       \
            std::move(#name),                                                                        \
            [](RenderTechnique* pTechnique, const SR_XML_NS::Node& node) -> SR_GRAPH_NS::BasePass* { \
                BasePass* pPass = new name(pTechnique);                                              \
                if (!pPass->Load(node)) {                                                            \
                    delete pPass;                                                                    \
                    pPass = nullptr;                                                                 \
                }                                                                                    \
                return pPass;                                                                        \
            }                                                                                        \
        )).second;                                                                                   \

#define SR_ALLOCATE_RENDER_PASS(pRenderTechnique, passNode)                                          \
    (SR_GRAPH_NS::GetRenderPassMap().count(passNode.Name()) == 0 ? nullptr :                         \
        SR_GRAPH_NS::GetRenderPassMap().at(passNode.Name())(pRenderTechnique, passNode))             \


#endif //SRENGINE_BASEPASS_H
