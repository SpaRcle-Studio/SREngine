//
// Created by Monika on 05.10.2021.
//

#include <Graphics/Memory/MeshManager.h>

namespace SR_GRAPH_NS::Memory {
    MeshManager::VideoResourcesIter MeshManager::FindImpl(const std::string& resourceID, MeshMemoryType memType) {
        switch (memType) {
            case MeshMemoryType::VBO: {
                if (auto mem = m_VBOs.find(resourceID); mem != m_VBOs.end())
                    return mem;
                else
                    break;
            }
            case MeshMemoryType::IBO:
                if (auto mem = m_IBOs.find(resourceID); mem != m_IBOs.end())
                    return mem;
                else
                    break;
            default:
                SR_ERROR("MeshManager::FindImpl() : unknown type!");
                return VideoResourcesIter();
        }

        return VideoResourcesIter();
    }

    bool MeshManager::RegisterImpl(const std::string &resourceId, MeshMemoryType memType, uint32_t id) {
    #ifndef SR_RELEASE
        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("MeshManager::RegisterImpl() : register resource \"" + resourceId + "\"");
        }
    #endif

        switch (memType) {
            case MeshMemoryType::VBO: {
                m_VBOs[resourceId] = MeshVidMemInfo(id, memType);
                return true;
            }
            case MeshMemoryType::IBO:
                m_IBOs[resourceId] = MeshVidMemInfo(id, memType);
                return true;
            default:
                SR_ERROR("MeshManager::RegisterImpl() : unknown type!");
                return false;
        }
    }

    MeshManager::FreeResult MeshManager::FreeImpl(VideoResourcesIter iter, MeshMemoryType memType) {
        if (auto& memory = iter.value()->second; memory.m_usages == 1) {
        #ifndef SR_RELEASE
            const std::string resourceId = iter.value()->first;
        #endif
            switch (memType) {
                case MeshMemoryType::VBO: m_VBOs.erase(iter.value());
                    goto skip;
                case MeshMemoryType::IBO: m_IBOs.erase(iter.value());
                skip:
                #ifndef SR_RELEASE
                    if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
                        SR_LOG("MeshManager::FreeImpl() : free resource \"" + resourceId + "\"");
                    }
                #endif
                    return FreeResult::Freed;
                case MeshMemoryType::Unknown:
                default:
                    SR_ERROR("MeshManager::FreeImpl() : unknown type!");
                    return FreeResult::UnknownMem;
            }
        }
        else {
            memory.m_usages--;
            return FreeResult::EndUse;
        }
    }

    void MeshManager::OnSingletonDestroy() {
        if (!m_VBOs.empty())
            SR_WARN(Helper::Format("MeshManager::OnSingletonDestroy() : VBOs isn't empty! \n\tCount = %i \n\t"
                                   "Memory leak possible.", m_VBOs.size()));

        if (!m_IBOs.empty())
            SR_WARN(Helper::Format("MeshManager::OnSingletonDestroy() : IBOs isn't empty! \n\tCount = %i \n\t"
                                   "Memory leak possible.", m_IBOs.size()));

        m_VBOs.clear();
        m_IBOs.clear();
    }

    void MeshManager::PrintDump() {
        if (m_VBOs.empty() && m_IBOs.empty()) {
            return;
        }

        std::string dump = "MeshManager::PrintDump() : ";

        for (auto&& [resource, vbo] : m_VBOs) {
            dump += "\n\tVBO [" + resource + "] Usages = " + std::to_string(vbo.GetUsages());
        }

        for (auto&& [resource, ibo] : m_IBOs) {
            dump += "\n\tIBO [" + resource + "] Usages = " + std::to_string(ibo.GetUsages());
        }

        SR_INFO(dump);
    }

    uint32_t MeshVidMemInfo::Copy() {
    #ifndef SR_RELEASE
        if (m_type == MeshMemoryType::Unknown) {
            SR_WARN("MeshVidMemInfo::Copy() : unknown memory type!");
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            switch (m_type) {
                case MeshMemoryType::VBO: SR_LOG("MeshVidMemInfo::Copy() : copy VBO..."); break;
                case MeshMemoryType::IBO: SR_LOG("MeshVidMemInfo::Copy() : copy IBO..."); break;
                default: break;
            }
        }
    #endif

        m_usages++;
        return m_vidId;
    }
}
