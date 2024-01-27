//
// Created by Monika on 10.10.2023.
//

#ifndef SR_ENGINE_GRAPHICS_I_RENDER_TECHNIQUE_H
#define SR_ENGINE_GRAPHICS_I_RENDER_TECHNIQUE_H

#include <Utils/Settings.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/SafePointer.h>

#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Memory/IGraphicsResource.h>

#include <Graphics/Pass/GroupPass.h>
#include <Graphics/Pass/PassQueue.h>

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
    class BasePass;

    class IRenderTechnique : public Memory::IGraphicsResource, public GroupPass {
    public:
        using CameraPtr = Types::Camera*;
        using Super = Memory::IGraphicsResource;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using Context = RenderContext*;
        SR_INLINE static const std::string DEFAULT_RENDER_TECHNIQUE = "Engine/Configs/MainRenderTechnique.xml";
    public:
        IRenderTechnique();
        ~IRenderTechnique() override;

    public:
        void Prepare() override;
        bool Overlay() override;
        bool Render() override;
        void Update() override;

        void FreeVideoMemory() override;

        void SetCamera(CameraPtr pCamera);
        void SetRenderScene(const RenderScenePtr& pRScene);

        SR_NODISCARD CameraPtr GetCamera() const noexcept { return m_camera; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const override;
        SR_NODISCARD bool IsEmpty() const;

        SR_GTYPES_NS::Mesh* PickMeshAt(float_t x, float_t y) const;
        SR_GTYPES_NS::Mesh* PickMeshAt(float_t x, float_t y, SR_UTILS_NS::StringAtom passName) const;
        SR_GTYPES_NS::Mesh* PickMeshAt(float_t x, float_t y, const std::vector<SR_UTILS_NS::StringAtom>& passFilter) const;
        SR_NODISCARD const PassQueues& GetQueues() const { return m_queues; }

    protected:
        virtual bool Build() { return true; }
        void SetDirty();
        void DeInitPasses();

        SR_NODISCARD uint64_t GetNodeHashName() const noexcept override { return 0; }
        SR_NODISCARD std::string GetNodeName() const noexcept override { return std::string(); }

    protected:
        RenderScenePtr m_renderScene;
        std::atomic<bool> m_dirty = false;
        std::atomic<bool> m_hasErrors = false;

        PassQueues m_queues;

    };
}

#endif //SR_ENGINE_GRAPHICS_I_RENDER_TECHNIQUE_H
