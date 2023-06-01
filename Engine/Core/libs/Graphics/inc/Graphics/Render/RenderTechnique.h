//
// Created by Monika on 17.07.2022.
//

#ifndef SRENGINE_RENDERTECHNIQUE_H
#define SRENGINE_RENDERTECHNIQUE_H

#include <Utils/Settings.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/SafePointer.h>

#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Memory/IGraphicsResource.h>

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
    class BasePass;

    /** Частично является настройкой, но может иметь множество экземпляров */
    class RenderTechnique : public SR_UTILS_NS::Settings, public Memory::IGraphicsResource {
        using CameraPtr = Types::Camera*;
        using Super = SR_UTILS_NS::Settings;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using Context = RenderContext*;
    private:
        RenderTechnique();

    public:
        ~RenderTechnique() override;

    public:
        static RenderTechnique* Load(const SR_UTILS_NS::Path& path);

    public:
        virtual void Prepare();
        virtual bool Overlay();
        virtual bool Render();
        virtual void Update();

        virtual void OnResize(const SR_MATH_NS::UVector2& size);
        virtual void OnSamplesChanged();

        void FreeVideoMemory() override;

        SR_NODISCARD CameraPtr GetCamera() const noexcept { return m_camera; }
        SR_NODISCARD Context GetContext() const noexcept { return m_context; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD std::string_view GetName() const;

        void SetCamera(CameraPtr pCamera);
        void SetRenderScene(const RenderScenePtr& pRScene);

        SR_NODISCARD BasePass* FindPass(uint64_t hashName) const;
        SR_NODISCARD BasePass* FindPass(const std::string& name) const;

    protected:
        bool Build();

        bool Load() override;
        bool Unload() override;

        bool LoadSettings(const SR_XML_NS::Node &node) override;
        void ClearSettings() override;

    private:
        void SetDirty();

    private:
        std::vector<BasePass*> m_passes;
        RenderScenePtr m_renderScene;
        CameraPtr m_camera = nullptr;
        Context m_context = nullptr;
        std::string m_name;
        std::atomic<bool> m_dirty = false;
        std::atomic<bool> m_hasErrors = false;
        Memory::UBOManager& m_uboManager;

    };
}


#endif //SRENGINE_RENDERTECHNIQUE_H
