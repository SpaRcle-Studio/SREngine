

# File IRenderTechnique.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**IRenderTechnique.h**](IRenderTechnique_8h.md)

[Go to the documentation of this file](IRenderTechnique_8h.md)


```C++
//
// Created by Monika on 10.10.2023.
//

#ifndef SR_ENGINE_GRAPHICS_I_RENDER_TECHNIQUE_H
#define SR_ENGINE_GRAPHICS_I_RENDER_TECHNIQUE_H

#include <Graphics/macros.h>

#include <Utils/Settings.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/SafePointer.h>

#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Memory/IGraphicsResource.h>

#include <Graphics/Pass/GroupPass.h>
#include <Graphics/Pass/PassQueue.h>

namespace SR_GTYPES_NS {
    class Camera;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class FrameBufferController;
    class RenderContext;
    class BasePass;

    class IRenderTechnique : public Memory::IGraphicsResource, public GroupPass {
    public:
        using FrameBufferControllerPtr = SR_HTYPES_NS::SharedPtr<FrameBufferController>;
        using CameraPtr = Types::Camera*;
        using Super = Memory::IGraphicsResource;
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
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

        bool Init() override;

        void FreeVideoMemory() override;

        void SetCamera(CameraPtr pCamera);
        void SetRenderScene(const RenderScenePtr& pRScene);

        SR_NODISCARD CameraPtr GetCamera() const noexcept { return m_camera; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const override;
        SR_NODISCARD bool IsEmpty() const;

        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnMultisampleChanged() override;

        SR_NODISCARD FrameBufferControllerPtr GetFrameBufferController(SR_UTILS_NS::StringAtom name) const;

        SR_GTYPES_NS::Mesh* PickMeshAt(const SR_MATH_NS::FPoint& pos) const;
        SR_GTYPES_NS::Mesh* PickMeshAt(float_t x, float_t y) const;
        SR_GTYPES_NS::Mesh* PickMeshAt(float_t x, float_t y, SR_UTILS_NS::StringAtom passName) const;
        SR_GTYPES_NS::Mesh* PickMeshAt(float_t x, float_t y, const std::vector<SR_UTILS_NS::StringAtom>& passFilter) const;
        SR_NODISCARD const PassQueues& GetQueues() const { return m_queues; }

    protected:
        virtual bool Build() { return true; }
        void SetDirty();
        void DeInitPasses();
        void ReleaseFrameBufferControllers();

        SR_NODISCARD uint64_t GetNodeHashName() const noexcept override { return 0; }
        SR_NODISCARD std::string GetNodeName() const noexcept override { return std::string(); }

    protected:
        RenderScenePtr m_renderScene;
        std::atomic<bool> m_dirty = false;
        std::atomic<bool> m_hasErrors = false;

        std::map<SR_UTILS_NS::StringAtom, FrameBufferControllerPtr> m_frameBufferControllers;

        PassQueues m_queues;

    };
}

#endif //SR_ENGINE_GRAPHICS_I_RENDER_TECHNIQUE_H
```


