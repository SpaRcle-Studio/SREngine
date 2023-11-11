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

    void* SingletonManager::GetSingleton(StringAtom name) noexcept {
        std::lock_guard lock(m_mutex);

        if (auto&& pIt = m_singletons.find(name); pIt != m_singletons.end()) {
            return pIt->second.pSingleton;
        }

        return nullptr;
    }

    void SingletonManager::DestroyAll() {
        std::lock_guard lock(m_mutex);

        for (auto pIt = m_singletons.begin(); pIt != m_singletons.end(); ) {
            auto&& [id, info] = *pIt;

            if (info.pSingletonBase->IsSingletonCanBeDestroyed()) {
                info.pSingletonBase->OnSingletonDestroy();
                delete info.pSingletonBase;
                pIt = m_singletons.erase(pIt);
            }
            else {
                ++pIt;
            }
        }
    }

    void SingletonManager::Remove(StringAtom name) {
        std::lock_guard lock(m_mutex);

        if (auto&& pIt = m_singletons.find(name); pIt != m_singletons.end()) {
            m_singletons.erase(pIt);
        }
    }
}