//
// Created by Monika on 30.08.2023.
//

#ifndef SRENGINE_HASHMANAGER_H
#define SRENGINE_HASHMANAGER_H

#include <Utils/Common/Hashes.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    class HashManager : public SR_UTILS_NS::Singleton<HashManager> {
        friend class SR_UTILS_NS::Singleton<HashManager>;
        using Hash = uint64_t;
    public:
        void InitSingleton() override;

        SR_NODISCARD const std::string& HashToString(Hash hash) const;
        SR_NODISCARD bool Exists(Hash hash) const;
        Hash AddHash(const std::string& str);

    private:
        ska::flat_hash_map<Hash, std::string> m_strings;

    };
}

#endif //SRENGINE_HASHMANAGER_H
