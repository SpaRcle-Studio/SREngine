//
// Created by Monika on 15.06.2022.
//

#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    SingletonManager* GetSingletonManager() {
        static SingletonManager* singletonManager = nullptr;

        if (!singletonManager) {
            singletonManager = new SingletonManager();
        }

        return singletonManager;
    }

    void** SingletonManager::GetSingleton(uint64_t id) {
        return &m_singletons[id]; /// get or create
    }
}