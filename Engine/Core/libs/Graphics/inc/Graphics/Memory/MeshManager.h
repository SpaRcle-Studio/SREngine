//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_MESHMANAGER_H
#define GAMEENGINE_MESHMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Thread.h>

#include <Graphics/Types/Vertices.h>
#include <Graphics/Environment/PipeLine.h>

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

            explicit MeshVidMemInfo(uint32_t id, MeshMemoryType type)
                : m_vidId(id)
                , m_usages(1)
                , m_type(type)
            { }

        public:
            SR_NODISCARD uint32_t Copy();

        private:
            uint32_t m_vidId = SR_UINT32_MAX;
            uint32_t m_usages = 0;
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
            VideoResourcesIter FindImpl(const std::string& resourceID, MeshMemoryType memType);
            bool RegisterImpl(const std::string& resourceId, MeshMemoryType memType, uint32_t id);
            FreeResult FreeImpl(VideoResourcesIter iter, MeshMemoryType memType);

            void OnSingletonDestroy() override;

            template<Vertices::VertexType vertexType, MeshMemoryType memType> VideoResourcesIter Find(const std::string& resourceID) {
                if constexpr (memType == MeshMemoryType::VBO) {
                    return this->FindImpl(resourceID + SR_UTILS_NS::EnumReflector::ToString<Vertices::VertexType>(vertexType), memType);
                }
                else
                    return this->FindImpl(resourceID, memType);
            }

        public:
            template<Vertices::VertexType vertexType, MeshMemoryType memType> bool Register(const std::string_view& resourceId, uint32_t id) {
                return Register<vertexType, memType>(std::string(resourceId), id);
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> bool Register(const std::string& resourceID, uint32_t id) {
                SR_LOCK_GUARD

                if (Find<vertexType, memType>(resourceID).has_value()) {
                    SRHalt("MeshManager::Register() : memory already registered!");
                    return false;
                }

                if constexpr (memType == MeshMemoryType::VBO) {
                    return RegisterImpl(resourceID + SR_UTILS_NS::EnumReflector::ToString(vertexType), memType, id);
                }
                else
                    return RegisterImpl(resourceID, memType, id);
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> FreeResult Free(const std::string_view& resourceId) {
                return Free<vertexType, memType>(std::string(resourceId));
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> FreeResult Free(const std::string& resourceID) {
                SR_LOCK_GUARD

                if (auto iter = Find<vertexType, memType>(resourceID); !iter.has_value()) {
                    SR_ERROR("MeshManager::Free() : memory isn't registered! "
                                         "\n\tResource id: " + resourceID);
                    SRAssert(false);
                    return FreeResult::NotFound;
                }
                else
                    return this->FreeImpl(iter, memType);
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> int32_t CopyIfExists(const std::string& resourceID) {
                SR_LOCK_GUARD

                if (auto memory = Find<vertexType, memType>(resourceID); memory.has_value()) {
                    return memory.value()->second.Copy();
                }

                return SR_ID_INVALID;
            }

            template<Vertices::VertexType vertexType, MeshMemoryType memType> int32_t CopyIfExists(const std::string_view& resourceID) {
                SR_LOCK_GUARD

                if (auto memory = Find<vertexType, memType>(std::string(resourceID)); memory.has_value()) {
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
