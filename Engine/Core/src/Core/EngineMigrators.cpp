//
// Created by Monika on 27.03.2023.
//

#include <Core/EngineMigrators.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Migration.h>

namespace SR_CORE_NS {
    bool RegisterMigrators() {
        static const auto GAME_OBJECT_HASH_NAME = SR_HASH_STR("GameObject");
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(GAME_OBJECT_HASH_NAME, 1004, 1005, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());

            migrated.Write(marshal.Read<bool>());
            auto name = marshal.Read<std::string>();
            migrated.Write(name);
            migrated.Write(marshal.Read<uint64_t>());

            auto&& measurement = static_cast<SR_UTILS_NS::Measurement>(marshal.Read<int8_t>());

            migrated.Write<uint8_t>(static_cast<uint8_t>(measurement));

            switch (measurement) {
                case SR_UTILS_NS::Measurement::Space2D:
                case SR_UTILS_NS::Measurement::Space3D:
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::Vector3<double>>(SR_MATH_NS::Vector3<double>(0.0)).Cast<SR_MATH_NS::Unit>(), SR_MATH_NS::FVector3(0.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::Vector3<double>>(SR_MATH_NS::Vector3<double>(0.0)).Cast<SR_MATH_NS::Unit>(), SR_MATH_NS::FVector3(0.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::Vector3<double>>(SR_MATH_NS::Vector3<double>(1.0)).Cast<SR_MATH_NS::Unit>(), SR_MATH_NS::FVector3(1.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::Vector3<double>>(SR_MATH_NS::Vector3<double>(1.0)).Cast<SR_MATH_NS::Unit>(), SR_MATH_NS::FVector3(1.f));
                    SR_FALLTHROUGH;
                default:
                    break;
            }

            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });

        return true;
    }
}
