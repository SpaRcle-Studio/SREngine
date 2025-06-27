

# File MeshManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Memory**](dir_dc778743e05f6f13753dd9bf5a4bd428.md) **>** [**MeshManager.h**](MeshManager_8h.md)

[Go to the documentation of this file](MeshManager_8h.md)


```C++
//
// Created by Monika on 05.10.2021.
//

#ifndef SR_ENGINE_MESHMANAGER_H
#define SR_ENGINE_MESHMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Thread.h>

#include <Graphics/Types/Vertices.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GTYPES_NS {
    class Mesh3D;
}

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_GRAPH_NS {
    class Pipeline;

    namespace Memory {
        class MeshManager;

        enum class MeshMemoryType {
            Unknown, VBO, IBO
        };

        class MeshVidMemInfo {
            friend class MeshManager;
        public:
            MeshVidMemInfo() = default;

            explicit MeshVidMemInfo(uint32_t size, uint32_t id, MeshMemoryType type)
                : m_vidId(id)
                , m_usages(1)
                , m_size(size)
                , m_type(type)
            { }

        public:
            SR_NODISCARD uint32_t Copy();
            SR_NODISCARD uint32_t Size() { return m_size; }

            SR_NODISCARD uint32_t GetUsages() const noexcept { return m_usages; }

        private:
            uint32_t m_vidId = SR_UINT32_MAX;
            uint32_t m_usages = 0;
            uint32_t m_size = 0;
            MeshMemoryType m_type = MeshMemoryType::Unknown;

        };

        class BakedMesh : public SR_HTYPES_NS::SharedPtr<BakedMesh> {
            using Super = SR_HTYPES_NS::SharedPtr<BakedMesh>;
            friend MeshManager;
        public:
            using Ptr = SR_HTYPES_NS::SharedPtr<BakedMesh>;

        public:
            BakedMesh()
                : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
            { }

            ~BakedMesh() override;

        public:
            void Destroy();

            SR_NODISCARD int32_t GetVBO() const noexcept { return m_VBO; }
            SR_NODISCARD int32_t GetIBO() const noexcept { return m_IBO; }
            SR_NODISCARD uint32_t GetCountIndices() const noexcept { return m_countIndices; }
            SR_NODISCARD uint32_t GetCountVertices() const noexcept { return m_countVertices; }
            SR_NODISCARD uint32_t GetUsages() const noexcept { return m_usages; }
            SR_NODISCARD uint64_t GetMeshIndex() const noexcept { return m_index; }
            SR_NODISCARD Pipeline* GetPipeline() const noexcept { return m_pipeline; }
            SR_NODISCARD SR_HTYPES_NS::RawMesh* GetRawMesh() const noexcept { return m_pRawMesh; }

            void AddUsePoint() {
                m_usages++;
            }

            void RemoveUsePoint() {
                if (m_usages > 0) {
                    m_usages--;
                    return;
                }
                SRHalt("BakedMesh::RemoveUsePoint() : usages is less than 0!");
            }

            static Ptr Bake(Pipeline* pPipeline, std::string_view path, uint32_t index, Vertices::VertexType vertexType);
            static Ptr Bake(Pipeline* pPipeline, SR_HTYPES_NS::RawMesh* pRawMesh, uint32_t index, Vertices::VertexType vertexType);

        private:
            uint32_t m_usages = 0;
            SR_HTYPES_NS::RawMesh* m_pRawMesh = nullptr;
            uint64_t m_index = 0;
            int32_t m_VBO = SR_ID_INVALID;
            int32_t m_IBO = SR_ID_INVALID;
            uint32_t m_countIndices = 0;
            uint32_t m_countVertices = 0;
            Pipeline* m_pipeline = nullptr;
        };

        class MeshManager : public SR_UTILS_NS::Singleton<MeshManager> {
            SR_REGISTER_SINGLETON(MeshManager)
            using HashTable = std::vector<SR_UTILS_NS::StringAtom>;
        public:
            typedef std::unordered_map<SR_UTILS_NS::StringAtom, MeshVidMemInfo> VideoResources;
            typedef std::optional<VideoResources::iterator> VideoResourcesIter;

            enum class FreeResult {
                Unknown, Freed, EndUse, NotFound, UnknownMem
            };

        private:
            MeshManager();
            ~MeshManager() override = default;

        public:
            SR_NODISCARD BakedMesh::Ptr BakeMesh(Pipeline* pPipeline, SR_HTYPES_NS::RawMesh* pRawMesh, uint32_t index, Vertices::VertexType vertexType);

            template<MeshMemoryType memType> bool Register(const std::string_view& identifier, uint32_t size, uint32_t id, Vertices::VertexType vertexType);
            template<Vertices::VertexType vertexType, MeshMemoryType memType> bool Register(const std::string_view& identifier, uint32_t size, uint32_t id);

            template<MeshMemoryType memType> FreeResult Free(int32_t id);

            template<MeshMemoryType memType> int32_t CopyIfExists(const std::string_view& identifier, Vertices::VertexType vertexType);
            template<Vertices::VertexType vertexType, MeshMemoryType memType> int32_t CopyIfExists(const std::string_view& identifier);
            template<Vertices::VertexType vertexType, MeshMemoryType memType> uint32_t Size(const std::string_view& identifier);

        private:
            VideoResourcesIter FindById(int32_t id, MeshMemoryType memType);
            VideoResourcesIter FindImpl(SR_UTILS_NS::StringAtom id, MeshMemoryType memType);

            bool RegisterImpl(const std::string_view& identifier, MeshMemoryType memType, uint32_t size, uint32_t id);
            FreeResult FreeImpl(VideoResourcesIter iter, MeshMemoryType memType);

            void OnSingletonDestroy() override;

            template<MeshMemoryType memType> VideoResourcesIter Find(const std::string_view& identifier, Vertices::VertexType vertexType);

        private:
            VideoResources m_IBOs;
            VideoResources m_VBOs;

            HashTable m_IBOTable;
            HashTable m_VBOTable;

        };


        template<MeshMemoryType memType>
        bool MeshManager::Register(const std::string_view& identifier, uint32_t size, uint32_t id, Vertices::VertexType vertexType) {
            SR_TRACY_ZONE;
            SR_LOCK_GUARD;

            if (auto iter = Find<memType>(std::string(identifier), vertexType); iter.has_value()) {
                SRHalt("MeshManager::Register() : memory already registered!");
                return false;
            }

            if constexpr (memType == MeshMemoryType::VBO) {
                return RegisterImpl(std::string(identifier)
                    + SR_UTILS_NS::EnumReflector::ToStringAtom(vertexType).ToStringRef(), memType, size, id);
            }
            else {
                return RegisterImpl(identifier, memType, size, id);
            }
        }

        template<Vertices::VertexType vertexType, MeshMemoryType memType>
        bool MeshManager::Register(const std::string_view& identifier, uint32_t size, uint32_t id) {
            SR_TRACY_ZONE;
            SR_LOCK_GUARD;

            if (Find<memType>(identifier, vertexType).has_value()) {
                SRHalt("MeshManager::Register() : memory already registered!");
                return false;
            }

            if constexpr (memType == MeshMemoryType::VBO) {
                return RegisterImpl(std::string(identifier)
                    + SR_UTILS_NS::EnumReflector::ToStringAtom(vertexType).ToStringRef(), memType, size, id);
            }
            else {
                return RegisterImpl(identifier, memType, size, id);
            }
        }

        template<MeshMemoryType memType> MeshManager::FreeResult MeshManager::Free(int32_t id) {
            SR_TRACY_ZONE;
            SR_LOCK_GUARD;

            if (auto iter = FindById(id, memType); !iter.has_value()) {
                SRHalt("Memory isn't registered!");
                return FreeResult::NotFound;
            }
            else {
                return FreeImpl(iter, memType);
            }
        }

        template<MeshMemoryType memType>
        int32_t MeshManager::CopyIfExists(const std::string_view &identifier, Vertices::VertexType vertexType) {
            SR_LOCK_GUARD;
            SR_TRACY_ZONE;

            if (auto memory = Find<memType>(identifier, vertexType); memory.has_value()) {
                return memory.value()->second.Copy();
            }

            return SR_ID_INVALID;
        }

        template<Vertices::VertexType vertexType, MeshMemoryType memType>
        int32_t MeshManager::CopyIfExists(const std::string_view& identifier) {
            return CopyIfExists<memType>(identifier, vertexType);
        }

        template<Vertices::VertexType vertexType, MeshMemoryType memType>
        uint32_t MeshManager::Size(const std::string_view& identifier) {
            SR_TRACY_ZONE;
            SR_LOCK_GUARD;

            if (auto memory = Find<memType>(std::string(identifier), vertexType); memory.has_value()) {
                return memory.value()->second.Size();
            }

            return 0;
        }

        template<MeshMemoryType memType>
        MeshManager::VideoResourcesIter MeshManager::Find(const std::string_view& identifier, Vertices::VertexType vertexType) {
            SR_TRACY_ZONE;

            if constexpr (memType == MeshMemoryType::VBO) {
                SR_UTILS_NS::StringAtom id = (std::string(identifier) + SR_UTILS_NS::EnumReflector::ToStringAtom(vertexType).ToStringRef());
                return FindImpl(id, memType);
            }

            if constexpr (memType == MeshMemoryType::IBO) {
                return FindImpl(identifier, memType);
            }

            SRHalt("Unknown memory type!");
            return std::nullopt;
        }
    }
}


#endif //SR_ENGINE_MESHMANAGER_H
```


