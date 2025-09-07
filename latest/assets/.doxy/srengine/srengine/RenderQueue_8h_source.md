

# File RenderQueue.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**RenderQueue.h**](RenderQueue_8h.md)

[Go to the documentation of this file](RenderQueue_8h.md)


```C++
//
// Created by Monika on 02.06.2024.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_RENDER_QUEUE_H
#define SR_ENGINE_GRAPHICS_MESH_RENDER_QUEUE_H

#include <Graphics/Utils/MeshUtils.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/SortedVector.h>
#include <Graphics/Memory/UBOManager.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Mesh;
}

namespace SR_GRAPH_NS {
    class MeshDrawerPass;
    class RenderStrategy;
    class RenderContext;
    class RenderScene;

    struct RenderQueueInfo;

    class RenderQueue : public SR_HTYPES_NS::SharedPtr<RenderQueue> {
        using Super = SR_HTYPES_NS::SharedPtr<RenderQueue>;
        using ShaderPtr = SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Shader>;
        using VBO = uint32_t;
        using Layer = SR_UTILS_NS::StringAtom;

        struct MeshShaderPair {
            SR_GTYPES_NS::Mesh* pMesh;
            RenderQueueInfo* pInfo;
        };
    public:
        enum QueueState : uint8_t {
            QUEUE_STATE_OK = 0,

            QUEUE_STATE_ERROR          = 1 << 1,
            QUEUE_STATE_VBO_ERROR      = QUEUE_STATE_ERROR | 1 << 2,
            QUEUE_STATE_SHADER_ERROR   = QUEUE_STATE_ERROR | 1 << 3,
            QUEUE_STATE_NOT_RENDERED   = QUEUE_STATE_ERROR | 1 << 4,
            QUEUE_STATE_WAIT_REGISTER  = QUEUE_STATE_ERROR | 1 << 5,
            QUEUE_STATE_MISSING_SHADER = QUEUE_STATE_ERROR | 1 << 6,
        };
        typedef uint8_t QueueStateFlags;

        struct MeshInfo {
            VBO vbo = 0;
            SR_GTYPES_NS::Mesh* pMesh = nullptr;
            SR_GTYPES_NS::Shader* pShader = nullptr;
            int64_t priority = 0;
            QueueStateFlags state = QUEUE_STATE_NOT_RENDERED;

            bool operator==(const MeshInfo& other) const noexcept {
                return
                    pShader == other.pShader &&
                    vbo == other.vbo &&
                    pMesh == other.pMesh &&
                    priority == other.priority;
            }
        };

        struct RenderQueueLessPredicate {
            SR_NODISCARD bool operator()(const MeshInfo& left, const MeshInfo& right) const noexcept {
                if (left.priority != right.priority) SR_UNLIKELY_ATTRIBUTE {
                    return left.priority < right.priority;
                }

                if (left.pShader != right.pShader) SR_LIKELY_ATTRIBUTE {
                    return left.pShader < right.pShader;
                }

                if (left.vbo != right.vbo) SR_UNLIKELY_ATTRIBUTE {
                    return left.vbo < right.vbo;
                }

                return left.pMesh < right.pMesh;
            }
        };

       // struct ShaderInfo {
      //      ShaderInfo() = default;
      //      ShaderInfo(SR_GTYPES_NS::Shader* pShader) : info(pShader) { }
      //      ShaderUseInfo info = {};
      //      uint32_t count = 0;
      //  };

       // struct ShaderQueueLessPredicate {
       //     SR_NODISCARD bool operator()(const ShaderUseInfo& left, const ShaderUseInfo& right) const noexcept {
       //         return left.pShader < right.pShader;
       //     }
       // };

        using Queue = SR_HTYPES_NS::SortedVector<MeshInfo, RenderQueueLessPredicate>;

    public:
        RenderQueue(RenderStrategy* pStrategy, MeshDrawerPass* pDrawer);
        virtual ~RenderQueue();

        void Register(const MeshRegistrationInfo& info);
        void UnRegister(const MeshRegistrationInfo& info);

        void Init();

        bool Render();
        void Update();

        void OnMeshDirty(SR_GTYPES_NS::Mesh* pMesh, RenderQueueInfo* pInfo);

        SR_NODISCARD const std::vector<std::pair<Layer, Queue>>& GetQueues() const noexcept { return m_queues; }

    protected:
        virtual void CustomDrawMesh(const MeshInfo& info) { }

        SR_NODISCARD MeshDrawerPass* GetMeshDrawerPass() const noexcept { return m_meshDrawerPass; }

    private:
        void UpdateShaders();
        void UpdateMeshes();
        void UpdateAllMeshes();

        SR_NODISCARD bool IsSuitable(const MeshRegistrationInfo& info) const;

        void Render(const SR_UTILS_NS::StringAtom& layer, Queue& queue);

        SR_NODISCARD MeshInfo* SR_FASTCALL FindNextShader(Queue& queue, MeshInfo* pElement);
        SR_NODISCARD MeshInfo* SR_FASTCALL FindNextVBO(Queue& queue, MeshInfo* pElement);

        bool SR_FASTCALL UseShader(SR_GTYPES_NS::Shader* pShader);

        void PrepareLayers();

        //SR_NODISCARD SR_GRAPH_NS::ShaderUseInfo GetShaderUseInfo(const MeshRegistrationInfo& info) const;

    protected:
        bool m_customMeshDraw = false;

    private:
        bool m_multiFrameMode = false;
        bool m_updateMeshesOnDemand = false;
        bool m_rendered = false;
        bool m_isInitialized = false;

        uint64_t m_layersStateHash = 0;

        Memory::UBOManager& m_uboManager;

        SR_UTILS_NS::StringAtom m_renderStageId;

        std::vector<std::pair<Layer, Queue>> m_queues;

        SR_HTYPES_NS::SortedVector<SR_GTYPES_NS::Shader*> m_shaders;
        std::vector<MeshShaderPair> m_meshes;
        std::vector<MeshShaderPair> m_tempMeshes;

        MeshDrawerPass* m_meshDrawerPass = nullptr;
        RenderContext* m_renderContext = nullptr;
        RenderStrategy* m_renderStrategy = nullptr;
        RenderScene* m_renderScene = nullptr;
        Pipeline* m_pipeline = nullptr;

    };

    struct RenderQueueInfo {
        RenderQueue* pRenderQueue;
        SR_GTYPES_NS::Shader* pShader;
        bool dirtyUniformsFrames[3];
        bool inUpdateQueue = false;

        bool operator==(const RenderQueueInfo& other) const {
            return pRenderQueue == other.pRenderQueue;
        }
    };

    struct MeshRenderQueues {
        constexpr static size_t MaxQueues = 64;
        RenderQueueInfo queues[MaxQueues];
        uint8_t count = 0;
        uint8_t maxCount = 0;

        void Clear() {
            count = 0;
            maxCount = 0;
            for (auto& q : queues) {
                q = {};
            }
        }

        SR_NODISCARD RenderQueueInfo* data() { return &queues[0]; }
        SR_NODISCARD size_t size() const { return maxCount; }

        SR_NODISCARD RenderQueueInfo* Find(RenderQueue* pQueue) {
            SR_TRACY_ZONE;
            for (size_t i = 0; i < maxCount; ++i) {
                if (queues[i].pRenderQueue == pQueue) {
                    return &queues[i];
                }
            }
            return nullptr;
        }

        SR_NODISCARD RenderQueueInfo* Add(RenderQueue* pQueue) {
            SR_TRACY_ZONE;
            if (count >= MaxQueues) {
                SRHalt("MeshRenderQueues::Add() : max queues limit reached!");
                return nullptr;
            }
            for (size_t i = 0; i < MaxQueues; ++i) {
                if (queues[i].pRenderQueue == nullptr) {
                    queues[i].pRenderQueue = pQueue;
                    count++;
                    maxCount = SR_MAX(maxCount, i + 1);
                    return &queues[i];
                }
            }
            SRHalt("MeshRenderQueues::Add() : queue not found, but should be added!");
            return nullptr;
        }

        RenderQueueInfo Remove(RenderQueue* pQueue) {
            SR_TRACY_ZONE;
            for (size_t i = 0; i < maxCount; ++i) {
                if (queues[i].pRenderQueue == pQueue) {
                    RenderQueueInfo tmp = queues[i];
                    queues[i] = {};
                    --count;
                    return tmp;
                }
            }
            SRHalt("MeshRenderQueues::Remove() : queue not found!");
            return {};
        }
    };

    static constexpr size_t SIZE_OF_MESH_RENDER_QUEUES_CLASS = sizeof(MeshRenderQueues);

    struct RenderQueuePredicate {
        using Element = RenderQueueInfo;
        SR_NODISCARD bool operator()(const Element& left, const Element& right) const noexcept {
            return left.pRenderQueue < right.pRenderQueue;
        }
    };
}

#endif //SR_ENGINE_GRAPHICS_MESH_RENDER_QUEUE_H
```


