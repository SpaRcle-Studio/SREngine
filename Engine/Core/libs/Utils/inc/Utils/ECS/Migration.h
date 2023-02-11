//
// Created by Monika on 01.01.2023.
//

#ifndef SRENGINE_MIGRATION_H
#define SRENGINE_MIGRATION_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/Marshal.h>

namespace SR_UTILS_NS {
    class Migration : public Singleton<Migration> {
        friend class Singleton<Migration>;
        using Version = uint16_t;
        using Migrator = SR_HTYPES_NS::Function<bool(SR_HTYPES_NS::Marshal&)>;
        struct MigrationInfo {
            Version from;
            Version to;
            Migrator migrator;
        };
    public:
        bool Migrate(uint64_t hashName, SR_HTYPES_NS::Marshal& pMarshal, Version version) const;

        bool RegisterMigrator(uint64_t hashName, Version from, Version to, Migrator&& migrator);

    private:
        std::map<uint64_t, std::vector<MigrationInfo>> m_migrators;

    };
}

#endif //SRENGINE_MIGRATION_H
