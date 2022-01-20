//
// Created by Monika on 16.01.2022.
//

#include <GUI/NodeManager.h>
#include <Debug.h>

using namespace Framework::Graphics::GUI;

uintptr_t NodeManager::AllocUniqueId(void* ptr) {
    std::lock_guard<std::mutex> lock(m_mutex);

retry:
    uintptr_t id = static_cast<uintptr_t>(Random::Instance().Int64());

    if (m_uniques.count(id) == 1 || id == UINTPTR_MAX || id == 0) {
        Helper::Debug::Warn("NodeManager::AllocUniqueId() : collision detected! Id: " + std::to_string(id));
        goto retry;
    }

    m_uniques.insert(std::make_pair(id, ptr));

    return id;
}

void NodeManager::FreeUniqueId(const uintptr_t& id) {
    if (id == UINTPTR_MAX)
        return;

    std::lock_guard<std::mutex> lock(m_mutex);

#ifdef SR_DEBUG
    if (m_uniques.count(id) == 0) {
        SRAssert2(false, Helper::Format("Id not found! Id: %ul", id));
        return;
    }
#endif

    m_uniques.erase(id);
}

void NodeManager::OnSingletonDestroy() {
    if (!m_uniques.empty())
        Helper::Debug::Warn(Helper::Format("NodeManager::OnSingletonDestroy() : %u uniques was been released!", m_uniques.size()));
}
