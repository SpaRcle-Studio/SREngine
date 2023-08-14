//
// Created by Monika on 16.01.2022.
//

#include <Utils/Debug.h>
#include <Utils/Common/Numeric.h>
#include <Utils/Common/StringFormat.h>

#include <Graphics/GUI/NodeManager.h>

namespace SR_GRAPH_NS::GUI {
    uintptr_t NodeManager::AllocUniqueId(void* ptr) {
        SR_LOCK_GUARD

    retry:
        uintptr_t id = static_cast<uintptr_t>(SR_UTILS_NS::Random::Instance().Int64());

        if (m_uniques.count(id) == 1 || id == SR_UINTPTR_MAX || id == 0) {
            SR_WARN("NodeManager::AllocUniqueId() : collision detected! Id: " + std::to_string(id));
            goto retry;
        }

        m_uniques.insert(std::make_pair(id, ptr));

        return id;
    }

    void NodeManager::FreeUniqueId(const uintptr_t& id) {
        if (id == SR_UINTPTR_MAX)
            return;

        SR_LOCK_GUARD

    #ifdef SR_DEBUG
        if (m_uniques.count(id) == 0) {
            SRAssert2(false, SR_UTILS_NS::Format("Id not found! Id: %ul", id));
            return;
        }
    #endif

        m_uniques.erase(id);
    }

    void NodeManager::OnSingletonDestroy() {
        if (!m_uniques.empty()) {
            SR_WARN(SR_UTILS_NS::Format("NodeManager::OnSingletonDestroy() : %u uniques was been released!", m_uniques.size()));
        }
    }
}