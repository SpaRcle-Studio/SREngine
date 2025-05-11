

# File MigrationManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**MigrationManager.h**](MigrationManager_8h.md)

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


