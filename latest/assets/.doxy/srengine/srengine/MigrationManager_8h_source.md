

# File MigrationManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**MigrationManager.h**](MigrationManager_8h.md)

[Go to the documentation of this file](MigrationManager_8h.md)


```C++
//
// Created by Monika on 01.01.2023.
//

#ifndef SR_ENGINE_MIGRATION_MANAGER_H
#define SR_ENGINE_MIGRATION_MANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Function.h>

namespace SR_UTILS_NS {
    class MigrationManager : public Singleton<MigrationManager> {
        SR_REGISTER_SINGLETON(MigrationManager)
        using Version = uint64_t;
        struct MigrationInfo {
            Version from;
            Version to;
            StringAtom factory;

            bool operator<(const MigrationInfo& other) const {
                return std::min(from, to) < std::min(other.from, other.to);
            }
        };
    public:
        SR_NODISCARD MigrationResult Migrate(SR_UTILS_NS::IDeserializer& deserializer, SR_UTILS_NS::Serializable& obj, Version from, Version to);

    private:
        void Initialize();

    private:
        bool m_isInitialized = false;
        std::map<StringAtom, std::vector<MigrationInfo>> m_migrations;

    };
}

#endif //SR_ENGINE_MIGRATION_MANAGER_H
```


