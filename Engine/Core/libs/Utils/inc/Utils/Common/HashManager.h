//
// Created by Monika on 30.08.2023.
//

#ifndef SRENGINE_HASHMANAGER_H
#define SRENGINE_HASHMANAGER_H

#include <Utils/Common/Hashes.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    struct StringHashInfo {
        std::string data;
        uint64_t hash = SR_ID_INVALID;
        uint64_t size = 0;
    };

    /// Не можем наследоваться от Singleton
    class HashManager : SR_UTILS_NS::NonCopyable {
        using Hash = uint64_t;
    private:
        HashManager() = default;
        ~HashManager() override = default;

    public:
        static HashManager& Instance();

    public:
        SR_NODISCARD const std::string& HashToString(Hash hash) const;
        SR_NODISCARD bool Exists(Hash hash) const;

        SR_NODISCARD StringHashInfo* GetOrAddInfo(const std::string& str);
        SR_NODISCARD StringHashInfo* GetOrAddInfo(const std::string_view& str);
        SR_NODISCARD StringHashInfo* GetOrAddInfo(const char* str);

        Hash AddHash(const std::string& str);
        Hash AddHash(const std::string_view& str);
        Hash AddHash(const char* str);

    private:
        SR_NODISCARD StringHashInfo* Register(std::string str, Hash hash);

    private:
        ska::flat_hash_map<Hash, StringHashInfo*> m_strings; /// NOLINT
        mutable std::recursive_mutex m_mutex;

    };
}

#define SR_HASH_STR_REGISTER(x) (SR_UTILS_NS::HashManager::Instance().AddHash(x))
#define SR_HASH_TYPE_NAME_STR_REGISTER(x) (SR_UTILS_NS::HashManager::Instance().AddHash(SR_GET_TYPE_NAME(x)))
#define SR_HASH_TO_STR(x) SR_UTILS_NS::HashManager::Instance().HashToString(x)

#endif //SRENGINE_HASHMANAGER_H
