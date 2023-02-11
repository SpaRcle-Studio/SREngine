//
// Created by Monika on 15.06.2022.
//

#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    SingletonManager* GetSingletonManager() noexcept {
        static SingletonManager* singletonManager = nullptr;

        if (!singletonManager) {
            singletonManager = new SingletonManager();
        }

        return singletonManager;
    }

    void** SingletonManager::GetSingleton(uint64_t id) noexcept {
        if (auto&& pIt = m_singletons.find(id); pIt != m_singletons.end()) {
            return &pIt->second;
        }

        auto&& pIt = m_singletons.insert(std::make_pair(id, nullptr));
        return &pIt.first->second;
    }
}