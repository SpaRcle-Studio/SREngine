

# File HashManager.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**HashManager.h**](HashManager_8h.md)

[Go to the documentation of this file](HashManager_8h.md)


```C++
//
// Created by Monika on 30.08.2023.
//

#ifndef SR_ENGINE_HASH_MANAGER_H
#define SR_ENGINE_HASH_MANAGER_H

#include <Utils/Common/Hashes.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    struct StringHashInfo {
        std::string data;
        std::string_view view;
        uint64_t hash = SR_ID_INVALID;
        uint64_t size = 0; 
    };

    class HashManager : SR_UTILS_NS::NonCopyable {
        using Hash = uint64_t;
        using Storage = ska::flat_hash_map<Hash, StringHashInfo*>;
    private:
        HashManager() = default;
        ~HashManager() override = default;

    public:
        SR_MAYBE_UNUSED static HashManager& Instance();

    public:
        void Lock() const { m_mutex.lock(); }
        void Unlock() const { m_mutex.unlock(); }

        SR_NODISCARD const std::string_view& HashToString(Hash hash) const;
        SR_NODISCARD StringAtom HashToStringAtom(Hash hash) const;
        SR_NODISCARD bool Exists(Hash hash) const;

        SR_NODISCARD const Storage& GetStorage() const { return m_strings; }

        SR_NODISCARD StringHashInfo* GetOrAddInfo(const std::string& str);
        SR_NODISCARD StringHashInfo* GetOrAddInfo(const std::string_view& str);
        SR_NODISCARD StringHashInfo* GetOrAddInfo(const char* str);

        Hash AddHash(const std::string& str);
        Hash AddHash(const std::string_view& str);
        Hash AddHash(const char* str);

    private:
        SR_NODISCARD StringHashInfo* Register(std::string str, Hash hash);

    private:
        Storage m_strings; 
        mutable std::recursive_mutex m_mutex;

    };

    struct ConstexprStringHashEntry {
        constexpr ConstexprStringHashEntry() = default;
        constexpr ConstexprStringHashEntry(std::string_view str, uint64_t hash)
            : str(str)
            , hash(hash)
        { }
        std::string_view str;
        uint64_t hash;
    };

    constexpr uint64_t ConstexprStringsMaxEntries = 512;

    struct GlobalStringRegistry {
        constexpr GlobalStringRegistry()
            : entries{}
            , count(0)
        { }

        mutable std::array<ConstexprStringHashEntry, ConstexprStringsMaxEntries> entries;
        mutable uint64_t count;

        constexpr uint64_t Register(std::string_view str, uint64_t hash) const {
            if (count < ConstexprStringsMaxEntries) {
                for (uint64_t i = 0; i < count; ++i) {
                    if (entries[i].hash == hash) {
                        return hash;
                    }
                }
                entries[++count] = ConstexprStringHashEntry(str, hash);
            }
            else {
                throw std::runtime_error("GlobalStringRegistry() : max entries reached!");
            }
            return hash;
        }

        SR_NODISCARD constexpr std::optional<std::string_view> FindConstexprStringByHash(uint64_t hash) const {
            for (uint64_t i = 0; i < count; ++i) {
                if (entries[i].hash == hash) {
                    return entries[i].str;
                }
            }
            return std::nullopt;
        }
    };

    //inline constexpr GlobalStringRegistry g_StringRegistry = GlobalStringRegistry();
}

#define SR_HASH_CONSTEXPR_STR_VIEW_REGISTER(x) (SR_UTILS_NS::g_StringRegistry.Register(x, SR_HASH_STR_VIEW(x)))
#define SR_HASH_STR_REGISTER(x) (SR_UTILS_NS::HashManager::Instance().AddHash(x))
#define SR_HASH_TYPE_NAME_STR_REGISTER(x) (SR_UTILS_NS::HashManager::Instance().AddHash(SR_GET_TYPE_NAME(x)))
#define SR_HASH_TO_STR(x) SR_UTILS_NS::HashManager::Instance().HashToString(x)
#define SR_HASH_TO_STR_ATOM(x) SR_UTILS_NS::HashManager::Instance().HashToStringAtom(x)

#endif //SR_ENGINE_HASH_MANAGER_H
```


