//
// Created by Monika on 01.01.2023.
//

#include <Utils/ECS/Migration.h>

namespace SR_UTILS_NS {
    SR_HTYPES_NS::Marshal Migration::Migrate(uint64_t hashName, SR_HTYPES_NS::Marshal& pMarshal, Migration::Version version) const {
        return SR_HTYPES_NS::Marshal();
    }

    bool Migration::RegisterMigrator(uint64_t hashName, Migration::Version from, Migration::Version to, Migration::Migrator&& migrator) {
        auto&& migrators = m_migrators[hashName];

        MigrationInfo migrationInfo;

        migrationInfo.from = from;
        migrationInfo.to = to;
        migrationInfo.migrator = migrator;

        migrators.emplace_back(std::move(migrationInfo));

        return true;
    }
}