//
// Created by Monika on 05.10.2021.
//

#include <Graphics/Memory/MeshManager.h>

namespace SR_GRAPH_NS::Memory {
    MeshManager::MeshManager() {
        const uint16_t reserve = 512;

        m_VBOs.reserve(reserve);
        m_IBOs.reserve(reserve);
        m_VBOTable.resize(reserve);
        m_IBOTable.resize(reserve);
    }

    MeshManager::VideoResourcesIter MeshManager::FindImpl(Hash hash, MeshMemoryType memType) {
        switch (memType) {
            case MeshMemoryType::VBO: {
                if (auto mem = m_VBOs.find(hash); mem != m_VBOs.end()) {
                    return mem;
                }
                break;
            }
            case MeshMemoryType::IBO: {
                if (auto mem = m_IBOs.find(hash); mem != m_IBOs.end()) {
                    return mem;
                }
                break;
            }
            default:
                SRHalt("MeshManager::FindImpl() : unknown memory type!");
                return std::nullopt;
        }

        return std::nullopt;
    }

    bool MeshManager::RegisterImpl(const std::string& resourceId, MeshMemoryType memType, uint32_t size, uint32_t id) {
    #ifndef SR_RELEASE
        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("MeshManager::RegisterImpl() : register resource \"" + resourceId + "\"");
        }
    #endif

        SRAssert2(id <= 32768, "Buffer overflow!");

        Hash hash = SR_HASH_STR(resourceId);

        switch (memType) {
            case MeshMemoryType::VBO: {
                m_VBOs[hash] = MeshVidMemInfo(size, id, memType);

                if (id >= m_VBOTable.size()) {
                    m_VBOTable.resize(SR_MAX(m_VBOTable.size() * 2, id + 1));
                }
                m_VBOTable[id] = hash;

                return true;
            }
            case MeshMemoryType::IBO: {
                m_IBOs[hash] = MeshVidMemInfo(size, id, memType);

                if (id >= m_IBOTable.size()) {
                    m_IBOTable.resize(SR_MAX(m_IBOTable.size() * 2, id + 1));
                }
                m_IBOTable[id] = hash;

                return true;
            }

            default:
                SR_ERROR("MeshManager::RegisterImpl() : unknown type!");
                return false;
        }
    }

    MeshManager::FreeResult MeshManager::FreeImpl(VideoResourcesIter iter, MeshMemoryType memType) {
        if (auto& memory = iter.value()->second; memory.m_usages == 1) {
            switch (memType) {
                case MeshMemoryType::VBO: m_VBOs.erase(iter.value());
                    goto skip;
                case MeshMemoryType::IBO: m_IBOs.erase(iter.value());
                skip:
                    return FreeResult::Freed;
                case MeshMemoryType::Unknown:
                default:
                    SRHalt("MeshManager::FreeImpl() : unknown memory type!");
                    return FreeResult::UnknownMem;
            }
        }
        else {
            --memory.m_usages;
            return FreeResult::EndUse;
        }
    }

    void MeshManager::OnSingletonDestroy() {
        if (!m_VBOs.empty()) {
            SR_WARN(SR_UTILS_NS::Format("MeshManager::OnSingletonDestroy() : VBOs isn't empty! \n\tCount = %i \n\t"
                                   "Memory leak possible.", m_VBOs.size()));
        }

        if (!m_IBOs.empty()) {
            SR_WARN(SR_UTILS_NS::Format("MeshManager::OnSingletonDestroy() : IBOs isn't empty! \n\tCount = %i \n\t"
                                   "Memory leak possible.", m_IBOs.size()));
        }

        m_VBOs.clear();
        m_IBOs.clear();

        m_VBOTable.clear();
        m_IBOTable.clear();
    }

    MeshManager::VideoResourcesIter MeshManager::FindById(int32_t id, MeshMemoryType memType) {
        HashTable* pHashTable = nullptr;

        switch (memType) {
            case MeshMemoryType::VBO: pHashTable = &m_VBOTable; break;
            case MeshMemoryType::IBO: pHashTable = &m_IBOTable; break;
            case MeshMemoryType::Unknown:
            default:
                SRHalt("MeshManager::FindById() : unknown memory type!");
                return std::nullopt;
        }

        if (id >= pHashTable->size()) {
            SRHalt("MeshManager::FindById() : invalid id!");
            return std::nullopt;
        }

        return FindImpl((*pHashTable)[id], memType);
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
