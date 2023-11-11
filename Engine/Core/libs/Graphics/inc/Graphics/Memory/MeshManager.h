//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_MESHMANAGER_H
#define GAMEENGINE_MESHMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Thread.h>

#include <Graphics/Types/Vertices.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GTYPES_NS {
    class Mesh3D;
}

namespace SR_GRAPH_NS {
    namespace Memory {
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

        class MeshManager : public SR_UTILS_NS::Singleton<MeshManager> {
            SR_REGISTER_SINGLETON(MeshManager)
            using Hash = uint64_t;
            using HashTable = std::vector<uint64_t>;
        public:
            typedef std::unordered_map<Hash, MeshVidMemInfo> VideoResources;
            typedef std::optional<VideoResources::iterator> VideoResourcesIter;

            enum class FreeResult {
                Unknown, Freed, EndUse, NotFound, UnknownMem
            };

        private:
            MeshManager();
            ~MeshManager() override = default;

        private:
            VideoResourcesIter FindById(int32_t id, MeshMemoryType memType);
            VideoResourcesIter FindImpl(Hash hash, MeshMemoryType memType);

            bool RegisterImpl(const std::string& identifier, MeshMemoryType memType, uint32_t size, uint32_t id);
            FreeResult FreeImpl(VideoResourcesIter iter, MeshMemoryType memType);

            void OnSingletonDestroy() override;

            template<Vertices::VertexType vertexType, MeshMemoryType memType> VideoResourcesIter Find(const std::string& identifier) {
                if constexpr (memType == MeshMemoryType::VBO) {
                    const Hash hash = SR_HASH_STR(identifier + SR_UTILS_NS::EnumReflector::ToString<Vertices::VertexType>(vertexType).ToStringRef());
                    return FindImpl(hash, memType);
                }

                if constexpr (memType == MeshMemoryType::IBO) {
                    const Hash hash = SR_HASH_STR(identifier);
                    return FindImpl(hash, memType);
                }

                SRHalt("Unknown memory type!");

                return std::nullopt;
            }

        public:
            template<Vertices::VertexType vertexType, MeshMemoryType memType> bool Register(const std::string_view& identifier, uint32_t size, uint32_t id) {
                return Register<vertexType, memType>(std::string(identifier), size, id);
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> bool Register(const std::string& identifier, uint32_t size, uint32_t id) {
                SR_LOCK_GUARD

                if (Find<vertexType, memType>(identifier).has_value()) {
                    SRHalt("MeshManager::Register() : memory already registered!");
                    return false;
                }

                if constexpr (memType == MeshMemoryType::VBO) {
                    return RegisterImpl(identifier + SR_UTILS_NS::EnumReflector::ToString(vertexType).ToStringRef(), memType, size, id);
                }
                else
                    return RegisterImpl(identifier, memType, size, id);
            }

            template<MeshMemoryType memType> FreeResult Free(int32_t id) {
                SR_LOCK_GUARD

                if (auto iter = FindById(id, memType); !iter.has_value()) {
                    SRHalt("Memory isn't registered!");
                    return FreeResult::NotFound;
                }
                else {
                    return FreeImpl(iter, memType);
                }
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> int32_t CopyIfExists(const std::string& identifier) {
                SR_LOCK_GUARD

                if (auto memory = Find<vertexType, memType>(identifier); memory.has_value()) {
                    return memory.value()->second.Copy();
                }

                return SR_ID_INVALID;
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> uint32_t Size(const std::string& identifier) {
                SR_LOCK_GUARD

                if (auto memory = Find<vertexType, memType>(std::string(identifier)); memory.has_value()) {
                    return memory.value()->second.Size();
                }

                return 0;
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> int32_t CopyIfExists(const std::string_view& identifier) {
                SR_LOCK_GUARD

                if (auto memory = Find<vertexType, memType>(std::string(identifier)); memory.has_value()) {
                    return memory.value()->second.Copy();
                }

                return SR_ID_INVALID;
            }

        private:
            VideoResources m_IBOs;
            VideoResources m_VBOs;

            HashTable m_IBOTable;
            HashTable m_VBOTable;

        };
    }
}


#endif //GAMEENGINE_MESHMANAGER_H
