//
// Created by Monika on 30.08.2023.
//

#include <Utils/Common/HashManager.h>

namespace SR_UTILS_NS {
    HashManager::Hash HashManager::AddHash(const std::string& str) {
        SR_LOCK_GUARD;
        auto&& hash = SR_HASH_STR(str);
        m_strings[hash] = str;
        return hash;
    }
    HashManager::Hash HashManager::AddHash(const std::string_view& str) {
        SR_LOCK_GUARD;
        auto&& hash = SR_HASH_STR_VIEW(str);
        m_strings[hash] = str;
        return hash;
    }

    const std::string& HashManager::HashToString(HashManager::Hash hash) const {
        SR_LOCK_GUARD;
        static std::string gDefault;
        if (auto&& pIt = m_strings.find(hash); pIt != m_strings.end()) {
            return pIt->second;
        }
        return gDefault;
    }

    bool HashManager::Exists(HashManager::Hash hash) const {
        SR_LOCK_GUARD;
        return m_strings.find(hash) != m_strings.end();
    }

    void HashManager::InitSingleton() {
        m_strings.reserve(1024);
        Singleton::InitSingleton();
    }
}