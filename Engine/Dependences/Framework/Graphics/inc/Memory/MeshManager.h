//
// Created by Monika on 05.10.2021.
//

#ifndef GAMEENGINE_MESHMANAGER_H
#define GAMEENGINE_MESHMANAGER_H

#include <Utils/Singleton.h>
#include <unordered_map>
#include <mutex>
#include <optional>
#include <Types/Vertices.h>

namespace Framework::Graphics {
    namespace Types {
        class Mesh3D;
    }

    namespace Memory {
        class MeshManager : public Helper::Singleton<MeshManager> {
            friend class Singleton<MeshManager>;
        public:
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
            ~MeshManager() = default;
        private:
            VideoResourcesIter FindImpl(const std::string& resourceID, MemoryType memType);
            bool RegisterImpl(const std::string& resourceId, MemoryType memType, uint32_t id);
            bool FreeImpl(VideoResourcesIter iter, MemoryType memType);
        private:
            void OnSingletonDestroy() override;
        private:
            template<typename MeshType> VideoResourcesIter Find(const std::string& resourceID, MemoryType type) {
                if (type == MemoryType::VBO) {
                    auto vertexType = GetVertexType<MeshType>();
                    return this->FindImpl(resourceID + Vertices::EnumTypeToString(vertexType), type);
                } else
                    return this->FindImpl(resourceID, type);
            }

            template<typename MeshType> Vertices::Type GetVertexType() {
                struct someType {};

                Vertices::Type vertexType = Vertices::Type::Unknown;

                if constexpr (std::is_same_v<MeshType, Types::Mesh3D>)
                    vertexType = Vertices::Type::Mesh3DVertex;
                else
                    static_assert(std::is_same_v<MeshType, someType>, "MeshManager::GetVertexType() : unknown mesh!");

                return vertexType;
            }
        public:
            template<typename MeshType> bool Register(const std::string& resourceID, MemoryType type, uint32_t id) {
                const std::lock_guard<std::mutex> lock(m_mutex);

                if (Find<MeshType>(resourceID, type).has_value()) {
                    Helper::Debug::Error("MeshManager::Register() : memory already registered!");
                    return false;
                }

                if (type == MemoryType::VBO) {
                    auto vertexType = GetVertexType<MeshType>();
                    return this->RegisterImpl(resourceID + Vertices::EnumTypeToString(vertexType), type, id);
                } else
                    return this->RegisterImpl(resourceID, type, id);
            }

            template<typename MeshType> bool Free(const std::string& resourceID, MemoryType type) {
                const std::lock_guard<std::mutex> lock(m_mutex);

                if (auto iter = Find<MeshType>(resourceID, type); !iter.has_value()) {
                    Helper::Debug::Error("MeshManager::Register() : memory isn't registered!");
                    return false;
                } else
                    return this->FreeImpl(iter, type);
            }

            template<typename MeshType> int32_t CopyIfExists(const std::string& resourceID, MemoryType type) {
                const std::lock_guard<std::mutex> lock(m_mutex);

                if (auto memory = Find<MeshType>(resourceID)) {
                    return memory->Copy();
                }

                return -1;
            }
        };
    }
}


#endif //GAMEENGINE_MESHMANAGER_H
