

# File RenderStrategy.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**RenderStrategy.h**](RenderStrategy_8h.md)

[Go to the documentation of this file](RenderStrategy_8h.md)


```C++
//
// Created by Monika on 17.01.2024.
//

#ifndef SR_ENGINE_RENDER_STRATEGY_H
#define SR_ENGINE_RENDER_STRATEGY_H

#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Utils/MeshUtils.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Render/RenderPredicates.h>

#include <Utils/ECS/Transform.h>

namespace SR_GTYPES_NS {
    class Mesh;
    class Shader;
}

namespace SR_GRAPH_NS {
    class RenderStrategy;
    class RenderScene;
    class RenderQueue;
    class MeshDrawerPass;
    class RenderContext;


    /*class IRenderStage : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        using MeshPtr = SR_GTYPES_NS::Mesh*;

    public:
        IRenderStage(RenderStrategy* pRenderStrategy, IRenderStage* pParent);

    public:
        using ShaderPtr = SR_GTYPES_NS::Shader*;

    public:
        virtual bool RegisterMesh(MeshRegistrationInfo& info) { return false; }
        virtual bool UnRegisterMesh(const MeshRegistrationInfo& info) { return false; }

        void PostUpdate() { m_uniformsDirty = false; }

        SR_NODISCARD virtual bool IsRendered() const { return m_isRendered; }
        SR_NODISCARD virtual bool IsEmpty() const { return true; }

        SR_NODISCARD RenderContext* GetRenderContext() const;
        SR_NODISCARD RenderScene* GetRenderScene() const;

        void SetError(SR_UTILS_NS::StringAtom error);

        SR_NODISCARD virtual bool IsValid() const { return true; }

        virtual void MarkUniformsDirty() { m_uniformsDirty = true; }

        virtual void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const { }

    protected:
        SR_NODISCARD bool IsNeedUpdate() const;

    protected:
        bool m_isRendered = false;
        IRenderStage* m_parent = nullptr;
        RenderStrategy* m_renderStrategy = nullptr;
        RenderContext* m_renderContext = nullptr;

    private:
        bool m_uniformsDirty = true;

    };*/


    /*class MeshRenderStage : public IRenderStage {
        using Super = IRenderStage;
        using MeshList = std::vector<SR_GTYPES_NS::Mesh*>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
    public:
        explicit MeshRenderStage(RenderStrategy* pRenderStrategy, IRenderStage* pParent);

        ~MeshRenderStage() override {
            SRAssert(m_meshes.empty());
        }

    public:
        SR_NODISCARD bool HasActiveMesh() const;

        virtual bool Render();

        void Update(ShaderUseInfo info);

        bool RegisterMesh(MeshRegistrationInfo& info) override;
        bool UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD bool IsEmpty() const override { return m_meshes.empty(); }

        void MarkUniformsDirty() override;

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    protected:
        Memory::UBOManager& m_uboManager;
        MeshList m_meshes;

    };


    class VBORenderStage : public MeshRenderStage {
        using Super = MeshRenderStage;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
    public:
        VBORenderStage(RenderStrategy* pRenderStrategy, IRenderStage* pParent, int32_t VBO);

    public:
        bool Render() override;

        SR_NODISCARD bool IsValid() const override { return m_VBO != SR_ID_INVALID; }

    private:
        int32_t m_VBO = -1;

    };


    class ShaderRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit ShaderRenderStage(RenderStrategy* pRenderStrategy, IRenderStage* pParent, SR_GTYPES_NS::Shader* pShader);
        ~ShaderRenderStage() override;

    public:
        bool Render();
        void Update();
        void PostUpdate();

        bool RegisterMesh(MeshRegistrationInfo& info) override;
        bool UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD bool IsEmpty() const override { return m_VBOStages.empty() && m_meshStage->IsEmpty(); }
        SR_NODISCARD bool IsValid() const override { return m_shader; }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        SR_NODISCARD bool HasActiveMesh() const;

    private:
        SR_GTYPES_NS::Shader* m_shader = nullptr;

        MeshRenderStage* m_meshStage = nullptr;
        std::map<int32_t, VBORenderStage*> m_VBOStages;

    };


    class MaterialRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit MaterialRenderStage(RenderStrategy* pRenderStrategy, IRenderStage* pParent, SR_GRAPH_NS::BaseMaterial* pMaterial);
        ~MaterialRenderStage() override;

    public:
        bool Render();
        void Update();
        void PostUpdate();

        bool RegisterMesh(MeshRegistrationInfo& info) override;
        bool UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD bool IsEmpty() const override { return m_VBOStages.empty() && m_meshStage->IsEmpty(); }
        SR_NODISCARD bool IsValid() const override { return m_material; }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        SR_NODISCARD bool HasActiveMesh() const;

    private:
        SR_GRAPH_NS::BaseMaterial* m_material = nullptr;

        MeshRenderStage* m_meshStage = nullptr;
        std::map<int32_t, VBORenderStage*> m_VBOStages;

    };


    class PriorityRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit PriorityRenderStage(RenderStrategy* pRenderStrategy, IRenderStage* pParent, int64_t priority)
            : Super(pRenderStrategy, pParent)
            , m_priority(priority)
        { }

        ~PriorityRenderStage() override {
            SRAssert(m_shaderStages.empty());
        }

    public:
        bool Render();
        void Update();
        void PostUpdate();

        bool RegisterMesh(MeshRegistrationInfo& info) override;
        bool UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD int64_t GetPriority() const noexcept { return m_priority; }

        SR_NODISCARD bool IsEmpty() const override { return m_shaderStages.empty(); }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        int64_t m_priority = 0;
        std::map<ShaderPtr, ShaderRenderStage*> m_shaderStages;

    };


    class LayerRenderStage : public IRenderStage {
        using Super = IRenderStage;
    public:
        explicit LayerRenderStage(RenderStrategy* pRenderStrategy, IRenderStage* pParent)
            : Super(pRenderStrategy, pParent)
        { }

        ~LayerRenderStage() override {
            SRAssert(m_priorityStages.empty() && m_shaderStages.empty());
        }

    public:
        bool Render();
        void Update();
        void PostUpdate();

        bool RegisterMesh(MeshRegistrationInfo& info) override;
        bool UnRegisterMesh(const MeshRegistrationInfo& info) override;

        SR_NODISCARD int64_t FindPriorityStageIndex(int64_t priority, bool nearest) const;

        SR_NODISCARD bool IsEmpty() const override { return m_priorityStages.empty() && m_shaderStages.empty(); }

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const override;

    private:
        void InsertPriorityStage(PriorityRenderStage* pStage);

    private:
        std::vector<PriorityRenderStage*> m_priorityStages;
        std::map<ShaderPtr, ShaderRenderStage*> m_shaderStages;

    };*/


    class RenderStrategy : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using RenderQueuePtr = SR_HTYPES_NS::SharedPtr<RenderQueue>;
    public:
        explicit RenderStrategy(RenderScene* pRenderScene);
        ~RenderStrategy() override;

    public:
        void Prepare();

        void RegisterMesh(SR_GTYPES_NS::Mesh* pMesh);
        bool UnRegisterMesh(SR_GTYPES_NS::Mesh* pMesh);
        void ReRegisterMesh(const MeshRegistrationInfo& info);

        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource) const;

        SR_NODISCARD RenderContext* GetRenderContext() const;
        SR_NODISCARD RenderScene* GetRenderScene() const { return m_renderScene; }
        SR_NODISCARD bool IsNeedCheckMeshActivity() const noexcept { return m_isNeedCheckMeshActivity; }
        SR_NODISCARD bool IsDebugModeEnabled() const noexcept { return m_enableDebugMode; }
        SR_NODISCARD bool IsUniformsDirty() const noexcept { return m_isUniformsDirty; }
        SR_NODISCARD const std::set<SR_UTILS_NS::StringAtom>& GetErrors() const noexcept { return m_errors; }
        SR_NODISCARD const std::set<SR_GTYPES_NS::Mesh*>& GetProblemMeshes() const noexcept { return m_problemMeshes; }

        void ClearErrors();
        void AddError(SR_UTILS_NS::StringAtom error) { m_errors.insert(error); }
        void AddProblemMesh(SR_GTYPES_NS::Mesh* pMesh) { m_problemMeshes.insert(pMesh); }
        void SetDebugMode(bool value);

        void ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const;

        void MarkUniformsDirty() { m_isUniformsDirty = true; }

        template<class QueueType = RenderQueue, class ReturnType=QueueType> SR_NODISCARD SR_HTYPES_NS::SharedPtr<ReturnType> BuildQueue(MeshDrawerPass* pDrawer);
        void RemoveQueue(RenderQueue* pQueue);

    private:
        void RegisterMesh(const MeshRegistrationInfo& info);
        bool UnRegisterMesh(const MeshRegistrationInfo& info);

        SR_NODISCARD bool BuildQueueImpl(const RenderQueuePtr& pQueue);

        MeshRegistrationInfo CreateMeshRegistrationInfo(SR_GTYPES_NS::Mesh* pMesh);

    private:
        std::vector<RenderQueuePtr> m_queues;

        RenderScene* m_renderScene = nullptr;

        std::set<SR_UTILS_NS::StringAtom> m_errors;
        std::set<SR_GTYPES_NS::Mesh*> m_problemMeshes;

        bool m_isNeedCheckMeshActivity = true;
        bool m_enableDebugMode = false;
        bool m_isUniformsDirty = true;

        std::vector<MeshRegistrationInfo> m_reRegisterMeshes;
        bool m_prepareState = false;

        SR_HTYPES_NS::ObjectPool<MeshPtr, uint32_t> m_meshPool;

    };

    template<class QueueType, class ReturnType> SR_HTYPES_NS::SharedPtr<ReturnType> RenderStrategy::BuildQueue(MeshDrawerPass* pDrawer) {
        SR_STATIC_ASSERT2((std::is_base_of_v<RenderQueue, QueueType>), "QueueType must be derived from RenderQueue");

        auto&& pQueue = RenderQueuePtr::MakeShared<QueueType, ReturnType>(this, pDrawer);

        if (!BuildQueueImpl(pQueue)) {
            SRHalt("Failed to build queue");
            pQueue.AutoFree();
            return nullptr;
        }

        m_queues.emplace_back(pQueue);

        return pQueue;
    }
}

#endif //SR_ENGINE_RENDER_STRATEGY_H
```


