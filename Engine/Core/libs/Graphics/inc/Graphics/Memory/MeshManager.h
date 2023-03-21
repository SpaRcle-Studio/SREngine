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
            friend class SR_UTILS_NS::Singleton<MeshManager>;
        public:
            typedef std::unordered_map<std::string, MeshVidMemInfo> VideoResources;
            typedef std::optional<std::unordered_map<std::string, MeshVidMemInfo>::iterator> VideoResourcesIter;

            enum class FreeResult {
                Unknown, Freed, EndUse, NotFound, UnknownMem
            };

        private:
            MeshManager() = default;
            ~MeshManager() override = default;

        private:
            VideoResourcesIter FindImpl(const std::string& identifier, MeshMemoryType memType);
            bool RegisterImpl(const std::string& identifier, MeshMemoryType memType, uint32_t size, uint32_t id);
            FreeResult FreeImpl(VideoResourcesIter iter, MeshMemoryType memType);

            void OnSingletonDestroy() override;

            template<Vertices::VertexType vertexType, MeshMemoryType memType> VideoResourcesIter Find(const std::string& identifier) {
                if constexpr (memType == MeshMemoryType::VBO) {
                    return this->FindImpl(identifier + SR_UTILS_NS::EnumReflector::ToString<Vertices::VertexType>(vertexType), memType);
                }
                else
                    return this->FindImpl(identifier, memType);
            }

        public:
            void PrintDump();

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
                    return RegisterImpl(identifier + SR_UTILS_NS::EnumReflector::ToString(vertexType), memType, size, id);
                }
                else
                    return RegisterImpl(identifier, memType, size, id);
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> FreeResult Free(const std::string_view& identifier) {
                return Free<vertexType, memType>(std::string(identifier));
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> FreeResult Free(const std::string& identifier) {
                SR_LOCK_GUARD

                if (auto iter = Find<vertexType, memType>(identifier); !iter.has_value()) {
                    SR_ERROR("MeshManager::Free() : memory isn't registered! "
                                         "\n\tResource id: " + identifier);
                    SRAssert(false);
                    return FreeResult::NotFound;
                }
                else
                    return this->FreeImpl(iter, memType);
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
            VideoResources m_IBOs = {};
            VideoResources m_VBOs = {};

        };
    }
}


#endif //GAMEENGINE_MESHMANAGER_H
