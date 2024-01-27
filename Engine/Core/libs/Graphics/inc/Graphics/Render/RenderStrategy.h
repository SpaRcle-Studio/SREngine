//
// Created by Monika on 17.01.2024.
//

#ifndef SR_ENGINE_RENDER_STRATEGY_H
#define SR_ENGINE_RENDER_STRATEGY_H

#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Utils/MeshUtils.h>

#include <Utils/ECS/Transform.h>

/**
    - Layer (Only render)
        - Priority (Only render)
            - Shader (Render/Update)
                * OnShaderUse
                - VBO (Render/Update)
                    * OnBindVBO
                    - Mesh
                    - Mesh
                    * OnUnBingVBO
               * OnShaderUnUse
*/

namespace SR_GTYPES_NS {
    class Mesh;
    class Shader;
}

namespace SR_GRAPH_NS {
    class RenderStrategy;
    class RenderScene;

    /// ----------------------------------------------------------------------------------------------------------------

    class IRenderStage : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        using MeshPtr = SR_GTYPES_NS::Mesh*;

    public:
        explicit IRenderStage(RenderStrategy* pRenderStrategy)
            : Super()
            , m_renderStrategy(pRenderStrategy)
        { }

    public:
        using ShaderPtr = SR_GTYPES_NS::Shader*;

    public:
        virtual bool RegisterMesh(const MeshRegistrationInfo& info) { return false; }
        virtual void UnRegisterMesh(const MeshRegistrationInfo& info) { }

        SR_NODISCARD virtual bool IsRendered() const { return m_isRendered; }
        SR_NODISCARD virtual bool IsEmpty() const { return true; }

        SR_NODISCARD RenderContext* GetRenderContext() const;
        SR_NODISCARD RenderScene* GetRenderScene() const;

        void SetError(SR_UTILS_NS::StringAtom error);

        virtual bool IsValid() const { return true; }

        virtual void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const { }

    protected:
        bool m_isRendered = false;
        RenderStrategy* m_renderStrategy = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class VBORenderStage : public IRenderStage {
        using Super = IRenderStage;
        using MeshList = std::vector<SR_GTYPES_NS::Mesh*>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
    public:
        VBORenderStage(RenderStrategy* pRenderStrategy, int32_t VBO);

        ~VBORenderStage() override {
            SRAssert(m_meshes.empty());
        }

    public:
        SR_NODISCARD bool HasActiveMesh() const;

        bool Render();
        void Update(ShaderPtr pShader);

        bool RegisterMesh(const MeshRegistrationInfo& info) override;
        void UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD bool IsEmpty() const override { return m_meshes.empty(); }
        SR_NODISCARD bool IsValid() const override { return m_VBO != SR_ID_INVALID; }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        int32_t m_VBO = -1;
        Memory::UBOManager& m_uboManager;
        MeshList m_meshes;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class ShaderRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit ShaderRenderStage(RenderStrategy* pRenderStrategy, SR_GTYPES_NS::Shader* pShader);
        ~ShaderRenderStage() override;

    public:
        bool Render();
        void Update();

        bool RegisterMesh(const MeshRegistrationInfo& info) override;
        void UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD bool IsEmpty() const override { return m_VBOStages.empty(); }
        SR_NODISCARD bool IsValid() const override { return m_shader; }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        SR_NODISCARD bool HasActiveMesh() const;

    private:
        SR_GTYPES_NS::Shader* m_shader = nullptr;

        std::map<int32_t, VBORenderStage*> m_VBOStages;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class PriorityRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit PriorityRenderStage(RenderStrategy* pRenderStrategy, int64_t priority)
            : Super(pRenderStrategy)
            , m_priority(priority)
        { }

        ~PriorityRenderStage() override {
            SRAssert(m_shaderStages.empty());
        }

    public:
        bool Render();
        void Update();

        bool RegisterMesh(const MeshRegistrationInfo& info) override;
        void UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD int64_t GetPriority() const noexcept { return m_priority; }

        SR_NODISCARD bool IsEmpty() const override { return m_shaderStages.empty(); }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        int64_t m_priority = 0;
        std::map<ShaderPtr, ShaderRenderStage*> m_shaderStages;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class LayerRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit LayerRenderStage(RenderStrategy* pRenderStrategy)
            : Super(pRenderStrategy)
        { }

        ~LayerRenderStage() override {
            SRAssert(m_priorityStages.empty() && m_shaderStages.empty());
        }

    public:
        bool Render();
        void Update();

        bool RegisterMesh(const MeshRegistrationInfo& info) override;
        void UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD int64_t FindPriorityStageIndex(int64_t priority, bool nearest) const;

        SR_NODISCARD bool IsEmpty() const override { return m_priorityStages.empty() && m_shaderStages.empty(); }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        void InsertPriorityStage(PriorityRenderStage* pStage);

    private:
        std::vector<PriorityRenderStage*> m_priorityStages;
        std::map<ShaderPtr, ShaderRenderStage*> m_shaderStages;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class RenderStrategy : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using VoidCallback = SR_HTYPES_NS::Function<void()>;
        using FilterCallback = SR_HTYPES_NS::Function<bool(SR_UTILS_NS::StringAtom)>;
        using PriorityCallback = SR_HTYPES_NS::Function<bool(int64_t)>;
        using ShaderCallback = SR_HTYPES_NS::Function<void(SR_GTYPES_NS::Shader*)>;
        using MeshShaderCallback = SR_HTYPES_NS::Function<void(SR_GTYPES_NS::Shader*,SR_GTYPES_NS::Mesh*)>;
        using ShaderReplaceCallback = SR_HTYPES_NS::Function<SR_GTYPES_NS::Shader*(SR_GTYPES_NS::Shader*)>;
    public:
        explicit RenderStrategy(RenderScene* pRenderScene);
        ~RenderStrategy() override;

    public:
        bool Render();
        void Update();

        void BindFilterCallback(FilterCallback callback) { m_layerFilter = std::move(callback); }
        void BindSharedUniformsCallback(ShaderCallback callback) { m_sharedUniformsCallback = std::move(callback); }
        void BindShaderReplaceCallback(ShaderReplaceCallback callback) { m_shaderReplaceCallback = std::move(callback); }
        void BindUniformsCallback(MeshShaderCallback callback) { m_uniformsCallback = std::move(callback); }
        void BindConstantsCallback(ShaderCallback callback) { m_constantsCallback = std::move(callback); }
        void BindSamplersCallback(ShaderCallback callback) { m_samplersCallback = std::move(callback); }
        void BindPriorityCallback(PriorityCallback callback) { m_priorityCallback = std::move(callback); }

        void RegisterMesh(SR_GTYPES_NS::Mesh* pMesh);
        void UnRegisterMesh(SR_GTYPES_NS::Mesh* pMesh);

        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource) const;

        SR_NODISCARD RenderContext* GetRenderContext() const;
        SR_NODISCARD RenderScene* GetRenderScene() const { return m_renderScene; }
        SR_NODISCARD ShaderPtr ReplaceShader(ShaderPtr pShader) const;
        SR_NODISCARD bool IsPriorityAllowed(int64_t priority) const;
        SR_NODISCARD bool IsNeedCheckMeshActivity() const noexcept { return m_isNeedCheckMeshActivity; }
        SR_NODISCARD bool IsDebugModeEnabled() const noexcept { return m_enableDebugMode; }
        SR_NODISCARD const std::set<SR_UTILS_NS::StringAtom>& GetErrors() const noexcept { return m_errors; }
        SR_NODISCARD const std::set<SR_GTYPES_NS::Mesh*>& GetProblemMeshes() const noexcept { return m_problemMeshes; }

        void ClearErrors();
        void AddError(SR_UTILS_NS::StringAtom error) { m_errors.insert(error); }
        void AddProblemMesh(SR_GTYPES_NS::Mesh* pMesh) { m_problemMeshes.insert(pMesh); }
        void SetDebugMode(bool value);

        void UseSharedUniforms(ShaderPtr pShader);
        void UseConstants(ShaderPtr pShader);
        void UseSamplers(ShaderPtr pShader);
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh);

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const;

    private:
        void RegisterMesh(const MeshRegistrationInfo& info);
        void UnRegisterMesh(const MeshRegistrationInfo& info);

    private:
        FilterCallback m_layerFilter;
        ShaderCallback m_sharedUniformsCallback;
        ShaderCallback m_constantsCallback;
        ShaderCallback m_samplersCallback;
        ShaderReplaceCallback m_shaderReplaceCallback;
        MeshShaderCallback m_uniformsCallback;
        PriorityCallback m_priorityCallback;

        RenderScene* m_renderScene = nullptr;

        bool m_isNeedCheckMeshActivity = true;

        std::set<SR_UTILS_NS::StringAtom> m_errors;
        std::set<SR_GTYPES_NS::Mesh*> m_problemMeshes;
        bool m_enableDebugMode = false;

        uint32_t m_meshCount = 0;

        std::map<SR_UTILS_NS::StringAtom, LayerRenderStage*> m_layers;

    };
}

#endif //SR_ENGINE_RENDER_STRATEGY_H
