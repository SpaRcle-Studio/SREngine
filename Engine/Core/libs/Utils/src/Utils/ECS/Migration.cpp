//
// Created by Monika on 01.01.2023.
//

#include <Utils/ECS/Migration.h>

namespace SR_UTILS_NS {
    bool Migration::Migrate(uint64_t hashName, SR_HTYPES_NS::Marshal& marshal, Version from, Version to) const {
        auto&& pIt = m_migrators.find(hashName);
        if (pIt == m_migrators.end()) {
            return false;
        }

        for (auto&& migrator : pIt->second) {
            if (migrator.from == from) {
                if (migrator.migrator(marshal)) {
                    from = migrator.to;
                }
                else {
                    break;
                }
            }
        }

        if (!pIt->second.empty() && pIt->second.back().to == to) {
            return true;
        }

        return false;
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