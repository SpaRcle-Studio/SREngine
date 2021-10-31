//
// Created by Monika on 05.10.2021.
//

#include "Memory/MeshManager.h"

#include <Debug.h>

namespace Framework::Graphics::Memory {
    MeshManager::VideoResourcesIter MeshManager::FindImpl(const std::string& resourceID, MemoryType memType) {
        switch (memType) {
            case MeshManager::MemoryType::VBO: {
                if (auto mem = m_VBOs.find(resourceID); mem != m_VBOs.end())
                    return mem;
                else
                    break;
            }
            case MeshManager::MemoryType::IBO:
                if (auto mem = m_IBOs.find(resourceID); mem != m_IBOs.end())
                    return mem;
                else
                    break;
            default:
                Helper::Debug::Error("MeshManager::FindImpl() : unknown type!");
                return VideoResourcesIter();
        }

        return VideoResourcesIter();
    }

    bool MeshManager::RegisterImpl(const std::string &resourceId, MeshManager::MemoryType memType, uint32_t id) {
    #ifndef SR_RELEASE
        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
            Helper::Debug::Log("MeshManager::RegisterImpl() : register resource \"" + resourceId + "\"");
    #endif

        switch (memType) {
            case MeshManager::MemoryType::VBO: {
                m_VBOs[resourceId] = VidMemInfo(id, memType);
                return true;
            }
            case MeshManager::MemoryType::IBO:
                m_IBOs[resourceId] = VidMemInfo(id, memType);
                return true;
            default:
                Helper::Debug::Error("MeshManager::RegisterImpl() : unknown type!");
                return false;
        }
    }

    MeshManager::FreeResult MeshManager::FreeImpl(VideoResourcesIter iter, MeshManager::MemoryType memType) {
        if (auto& memory = iter.value()->second; memory.m_usages == 1) {
        #ifndef SR_RELEASE
            const std::string resourceId = iter.value()->first;
        #endif
            switch (memType) {
                case VBO: m_VBOs.erase(iter.value());
                    goto skip;
                case IBO: m_IBOs.erase(iter.value());
                skip:
                #ifndef SR_RELEASE
                    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                        Helper::Debug::Log("MeshManager::FreeImpl() : free resource \"" + resourceId + "\"");
                #endif
                    return FreeResult::Freed;
                case Unknown:
                default:
                    Helper::Debug::Error("MeshManager::FreeImpl() : unknown type!");
                    return FreeResult::UnknownMem;
            }
        } else {
            memory.m_usages--;
            return FreeResult::EndUse;
        }
    }

    void MeshManager::OnSingletonDestroy() {
        if (!m_VBOs.empty())
            Helper::Debug::Warn(Helper::Format("MeshManager::OnSingletonDestroy() : "
                                               "VBOs isn't empty! \n\tCount = %i \n\t"
                                               "Memory leak possible.", m_VBOs.size()));

        if (!m_IBOs.empty())
            Helper::Debug::Warn(Helper::Format("MeshManager::OnSingletonDestroy() : "
                                               "IBOs isn't empty! \n\tCount = %i \n\t"
                                               "Memory leak possible.", m_IBOs.size()));

        m_VBOs.clear();
        m_IBOs.clear();
    }

    uint32_t MeshManager::VidMemInfo::Copy() {
    #ifndef SR_RELEASE
        if (m_type == MemoryType::Unknown)
            Helper::Debug::Warn("VidMemInfo::Copy() : unknown memory type!");

        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High) {
            switch (m_type) {
                case MemoryType::VBO: Helper::Debug::Log("VidMemInfo::Copy() : copy VBO..."); break;
                case MemoryType::IBO: Helper::Debug::Log("VidMemInfo::Copy() : copy IBO..."); break;
                default: break;
            }
        }
    #endif

        m_usages++;
        return m_vidId;
    }
}
