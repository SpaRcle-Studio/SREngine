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

    class IRenderTechnique : public Memory::IGraphicsResource {
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
        virtual void Prepare();
        virtual bool Overlay();
        virtual bool Render();
        virtual void Update();

        virtual void OnResize(const SR_MATH_NS::UVector2& size);
        virtual void OnSamplesChanged();

        void FreeVideoMemory() override;

        void SetCamera(CameraPtr pCamera);
        void SetRenderScene(const RenderScenePtr& pRScene);

        SR_NODISCARD CameraPtr GetCamera() const noexcept { return m_camera; }
        SR_NODISCARD Context GetContext() const noexcept { return m_context; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD std::string_view GetName() const;

        SR_NODISCARD BasePass* FindPass(uint64_t hashName) const;
        SR_NODISCARD BasePass* FindPass(const std::string& name) const;

        SR_NODISCARD const PassQueues& GetQueues() const { return m_queues; }

        template<typename T> SR_NODISCARD T* FindPass() const;

    protected:
        virtual bool Build() { return true; }
        void SetDirty();
        void DeInitPasses();

    protected:
        RenderScenePtr m_renderScene;
        CameraPtr m_camera = nullptr;
        Context m_context = nullptr;
        std::string m_name;
        std::atomic<bool> m_dirty = false;
        std::atomic<bool> m_hasErrors = false;
        Memory::UBOManager& m_uboManager;

        std::vector<BasePass*> m_passes;
        PassQueues m_queues;

    };

    template<typename T> T* IRenderTechnique::FindPass() const {
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

#endif //SR_ENGINE_GRAPHICS_I_RENDER_TECHNIQUE_H
