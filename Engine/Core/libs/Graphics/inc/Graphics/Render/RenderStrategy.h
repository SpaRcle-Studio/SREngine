//
// Created by Monika on 17.01.2024.
//

#ifndef SR_ENGINE_RENDER_STRATEGY_H
#define SR_ENGINE_RENDER_STRATEGY_H

#include <Graphics/Memory/UBOManager.h>

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

    struct MeshRegistrationInfo {
        SR_GTYPES_NS::Mesh* pMesh = nullptr;
        SR_GTYPES_NS::Shader* pShader = nullptr;
        int32_t VBO = -1;
        SR_UTILS_NS::StringAtom layer;
        std::optional<int64_t> priority;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    class IRenderStage : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
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

    protected:
        bool m_isRendered = false;
        RenderStrategy* m_renderStrategy = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class VBORenderStage : public IRenderStage {
        using Super = IRenderStage;
        using MeshList = std::vector<SR_GTYPES_NS::Mesh*>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
    public:
        explicit VBORenderStage(RenderStrategy* pRenderStrategy);

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

    private:
        Memory::UBOManager& m_uboManager;
        MeshList m_meshes;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class ShaderRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit ShaderRenderStage(RenderStrategy* pRenderStrategy)
            : Super(pRenderStrategy)
        { }

        ~ShaderRenderStage() override {
            SRAssert(m_VBOStages.empty());
        }

    public:
        bool Render();
        void Update();

        bool RegisterMesh(const MeshRegistrationInfo& info) override;
        void UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD bool IsEmpty() const override { return m_VBOStages.empty(); }

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

        SR_NODISCARD RenderContext* GetRenderContext() const;
        SR_NODISCARD RenderScene* GetRenderScene() const { return m_renderScene; }
        SR_NODISCARD ShaderPtr ReplaceShader(ShaderPtr pShader) const;
        SR_NODISCARD bool IsPriorityAllowed(int64_t priority) const;
        SR_NODISCARD bool IsNeedCheckMeshActivity() const noexcept { return m_isNeedCheckMeshActivity; }

        void UseSharedUniforms(ShaderPtr pShader);
        void UseConstants(ShaderPtr pShader);
        void UseSamplers(ShaderPtr pShader);
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh);

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

        std::map<SR_UTILS_NS::StringAtom, LayerRenderStage*> m_layers;

        std::unordered_map<MeshPtr, MeshRegistrationInfo> m_meshes;

    };
}

#endif //SR_ENGINE_RENDER_STRATEGY_H
