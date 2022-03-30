//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_MESHMANAGER_H
#define GAMEENGINE_MESHMANAGER_H

#include <Utils/Singleton.h>
#include <Types/Vertices.h>
#include <Environment/PipeLine.h>

namespace Framework::Graphics {
    namespace Types {
        class Mesh3D;
    }

    namespace Memory {
        class MeshManager : public Helper::Singleton<MeshManager> {
            friend class Helper::Singleton<MeshManager>;
        public:
            enum class FreeResult {
                Unknown, Freed, EndUse, NotFound, UnknownMem
            };

            enum MemoryType {
                Unknown, VBO, IBO
            };

            class VidMemInfo {
                friend class MeshManager;
            private:
                uint32_t m_vidId = UINT32_MAX;
                uint32_t m_usages = 0;
                MemoryType m_type = Unknown;
            public:
                VidMemInfo() = default;
                explicit VidMemInfo(uint32_t id, MemoryType type) : m_vidId(id), m_usages(1), m_type(type) {}
            public:
                [[nodiscard]] uint32_t Copy();
            };

            typedef std::unordered_map<std::string, VidMemInfo> VideoResources;
            typedef std::optional<std::unordered_map<std::string, VidMemInfo>::iterator> VideoResourcesIter;
        private:
            VideoResources m_IBOs = {};
            VideoResources m_VBOs = {};
            std::mutex m_mutex;
        private:
            MeshManager() = default;
            ~MeshManager() override = default;
        private:
            VideoResourcesIter FindImpl(const std::string& resourceID, MemoryType memType);
            bool RegisterImpl(const std::string& resourceId, MemoryType memType, uint32_t id);
            FreeResult FreeImpl(VideoResourcesIter iter, MemoryType memType);
        private:
            void OnSingletonDestroy() override;
        private:
            template<Vertices::Type vertexType, MemoryType memType> VideoResourcesIter Find(const std::string& resourceID) {
                if constexpr (memType == MemoryType::VBO) {
                    return this->FindImpl(resourceID + Vertices::EnumTypeToString(vertexType), memType);
                } else
                    return this->FindImpl(resourceID, memType);
            }
        public:
            template<Vertices::Type vertexType, MemoryType memType> bool Register(const std::string& resourceID, uint32_t id) {
                const std::lock_guard<std::mutex> lock(m_mutex);

                if (Find<vertexType, memType>(resourceID).has_value()) {
                    SR_ERROR("MeshManager::Register() : memory already registered!");
                    SRAssert(false);
                    return false;
                }

                if constexpr (memType == MemoryType::VBO) {
                    return this->RegisterImpl(resourceID + Vertices::EnumTypeToString(vertexType), memType, id);
                } else
                    return this->RegisterImpl(resourceID, memType, id);
            }

            template<Vertices::Type vertexType, MemoryType memType> FreeResult Free(const std::string& resourceID) {
                const std::lock_guard<std::mutex> lock(m_mutex);

                if (auto iter = Find<vertexType, memType>(resourceID); !iter.has_value()) {
                    SR_ERROR("MeshManager::Free() : memory isn't registered! "
                                         "\n\tResource id: " + resourceID);
                    SRAssert(false);
                    return FreeResult::NotFound;
                } else
                    return this->FreeImpl(iter, memType);
            }

            template<Vertices::Type vertexType, MemoryType memType> int32_t CopyIfExists(const std::string& resourceID) {
                const std::lock_guard<std::mutex> lock(m_mutex);

                if (auto memory = Find<vertexType, memType>(resourceID); memory.has_value()) {
                    return memory.value()->second.Copy();
                }

                return SR_ID_INVALID;
            }
        };
    }
}


#endif //GAMEENGINE_MESHMANAGER_H
