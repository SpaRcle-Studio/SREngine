//
// Created by Monika on 30.08.2023.
//

#include <Utils/Common/HashManager.h>

namespace SR_UTILS_NS {
    HashManager& HashManager::Instance() {
        static HashManager instance;
        return instance;
    }

    HashManager::Hash HashManager::AddHash(const char* str) {
        return GetOrAddInfo(str)->hash;
    }

    HashManager::Hash HashManager::AddHash(const std::string& str) {
        return GetOrAddInfo(str)->hash;
    }

    HashManager::Hash HashManager::AddHash(const std::string_view& str) {
        return GetOrAddInfo(str)->hash;
    }

    const std::string& HashManager::HashToString(HashManager::Hash hash) const {
        SR_LOCK_GUARD;
        static std::string gDefault;
        if (auto&& pIt = m_strings.find(hash); pIt != m_strings.end()) {
            return pIt->second->data;
        }
        return gDefault;
    }

    StringAtom HashManager::HashToStringAtom(HashManager::Hash hash) const {
        SR_LOCK_GUARD;
        static StringAtom gDefault;
        if (auto&& pIt = m_strings.find(hash); pIt != m_strings.end()) {
            return StringAtom(pIt->second); /// NOLINT
        }
        return gDefault;
    }

    bool HashManager::Exists(HashManager::Hash hash) const {
        SR_LOCK_GUARD;
        return m_strings.find(hash) != m_strings.end();
    }

    StringHashInfo* HashManager::Register(std::string str, Hash hash) {
        SR_LOCK_GUARD;

        auto&& pInfo = new StringHashInfo();
        pInfo->size = str.size();
        pInfo->data = std::move(str);
        pInfo->hash = hash;

        m_strings.insert(std::make_pair(hash, pInfo));

        return pInfo;
    }

    StringHashInfo* HashManager::GetOrAddInfo(const std::string& str) {
        SR_LOCK_GUARD;
        auto&& hash = SR_HASH_STR(str);
        if (auto&& pIt = m_strings.find(hash); pIt != m_strings.end()) {
            return pIt->second;
        }
        return Register(str, hash);
    }

    StringHashInfo* HashManager::GetOrAddInfo(const std::string_view& str) {
        SR_LOCK_GUARD;
        auto&& hash = SR_HASH_STR_VIEW(str);
        if (auto&& pIt = m_strings.find(hash); pIt != m_strings.end()) {
            return pIt->second;
        }
        return Register(str.data(), hash);
    }

    StringHashInfo* HashManager::GetOrAddInfo(const char* str) {
        SR_LOCK_GUARD;
        auto&& hash = SR_HASH_STR(str);
        if (auto&& pIt = m_strings.find(hash); pIt != m_strings.end()) {
            return pIt->second;
        }
        return Register(str, hash);
    }
}