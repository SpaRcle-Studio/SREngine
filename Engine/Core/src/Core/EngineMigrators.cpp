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
            /// --------------------------------------------------------------------------------------------------------
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

            /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });

        static const auto RIGID_BODY_3D_HASH_NAME = SR_HASH_STR("Rigidbody3D");
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(RIGID_BODY_3D_HASH_NAME, 1004, 1005, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());
            /// --------------------------------------------------------------------------------------------------------
            migrated.Write<int32_t>(marshal.Read<int32_t>());

            migrated.Write<SR_MATH_NS::Vector3<float_t>>(marshal.Read<SR_MATH_NS::Vector3<float_t>>(SR_MATH_NS::Vector3<float_t>(0.f)), SR_MATH_NS::Vector3<float_t>(0.f));
            migrated.Write<SR_MATH_NS::Vector3<float_t>>(marshal.Read<SR_MATH_NS::Vector3<float_t>>(SR_MATH_NS::Vector3<float_t>(1.f)), SR_MATH_NS::Vector3<float_t>(1.f));

            migrated.Write<float_t>(marshal.Read<float_t>());
            migrated.Write<bool>(marshal.Read<bool>());
            migrated.Write<bool>(marshal.Read<bool>());
            migrated.Write<std::string>("Engine/PhysicsMaterials/DefaultMaterial.physmat");

            migrated.Write<SR_MATH_NS::BVector3>(marshal.Read<SR_MATH_NS::BVector3>());
            migrated.Write<SR_MATH_NS::BVector3>(marshal.Read<SR_MATH_NS::BVector3>());

            /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });

        static const auto SKINNED_MESH_HASH_NAME = SR_HASH_STR("SkinnedMesh");
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(SKINNED_MESH_HASH_NAME, 1001, 1002, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());
            /// --------------------------------------------------------------------------------------------------------

            migrated.Write<int32_t>(marshal.Read<int32_t>()); /// mesh type
            migrated.Write<std::string>(marshal.Read<std::string>()); /// path
            migrated.Write<uint32_t>(marshal.Read<uint32_t>()); /// id

            migrated.Write<std::string>(marshal.Read<std::string>()); /// material

            SR_UTILS_NS::EntityRef ref;
            ref.Save(migrated);

            /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });

        return true;
    }
}
