//
// Created by Monika on 27.03.2023.
//

#include <Core/EngineMigrators.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Migration.h>
#include <Utils/ECS/LayerManager.h>

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
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(GAME_OBJECT_HASH_NAME, 1005, 1006, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());
            /// --------------------------------------------------------------------------------------------------------

            migrated.Write(false); /// is prefab

            /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(GAME_OBJECT_HASH_NAME, 1006, 1007, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());
            /// --------------------------------------------------------------------------------------------------------

            if (marshal.Read<bool>()) { /// is prefab
                migrated.Write<bool>(true);
            }
            else {
                migrated.Write<bool>(false);
                migrated.Write(marshal.Read<bool>());
                migrated.Write(marshal.Read<std::string>());
                migrated.Write(marshal.Read<uint64_t>());

                auto&& measurement = static_cast<SR_UTILS_NS::Measurement>(marshal.Read<int8_t>());

                migrated.Write<uint8_t>(static_cast<uint8_t>(measurement));

                if (measurement == SR_UTILS_NS::Measurement::Space2D) {
                    migrated.Write<uint32_t>(static_cast<uint32_t>(SR_UTILS_NS::Stretch::ShowAll));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(0.0)), SR_MATH_NS::FVector3(0.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(0.0)), SR_MATH_NS::FVector3(0.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(1.0)), SR_MATH_NS::FVector3(1.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(1.0)), SR_MATH_NS::FVector3(1.f));
                }
            }

            /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(GAME_OBJECT_HASH_NAME, 1007, 1008, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());
            /// --------------------------------------------------------------------------------------------------------

            if (marshal.Read<bool>()) { /// is prefab
                migrated.Write<bool>(true);  /// is prefab

                migrated.Write(marshal.Read<std::string>()); /// prefabPath
                migrated.Write(marshal.Read<std::string>()); /// objectName
                migrated.Write(marshal.Read<uint64_t>()); /// tag
                migrated.Write(marshal.Read<bool>()); /// isEnabled

                auto&& measurement = static_cast<SR_UTILS_NS::Measurement>(marshal.Read<uint8_t>()); /// measurement

                if (measurement == SR_UTILS_NS::Measurement::Space2D) {
                    migrated.Write<uint64_t>(53);
                }
                else {
                    migrated.Write<uint64_t>(51);
                }

                migrated.Write<uint16_t>(1000); /// version
                migrated.Write<uint8_t>(static_cast<uint8_t>(measurement)); /// measurement

                switch (measurement) {
                    case SR_UTILS_NS::Measurement::Space2D: {
                        migrated.Write<uint8_t>(static_cast<uint8_t>(marshal.Read<uint32_t>())); /// stretch
                        migrated.Write<uint8_t>(static_cast<uint8_t>(SR_UTILS_NS::Anchor::None)); /// anchor
                        SR_FALLTHROUGH;
                    }
                    case SR_UTILS_NS::Measurement::Space3D:
                        migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(0.f)), SR_MATH_NS::FVector3(0.f));
                        migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(0.f)), SR_MATH_NS::FVector3(0.f));
                        migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(1.f)), SR_MATH_NS::FVector3(1.f));
                        migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(1.f)), SR_MATH_NS::FVector3(1.f));
                        break;
                    default:
                        break;
                }

                /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
                migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

                marshal.SetData(migrated.Stream::View(), migrated.Size());
                marshal.SetPosition(position);

                return true;
            }
            else {
                migrated.Write<bool>(false);  /// is prefab
            }

            migrated.Write<bool>(marshal.Read<bool>()); /// enabled
            migrated.Write<std::string>(marshal.Read<std::string>()); /// name
            migrated.Write<uint64_t>(marshal.Read<uint64_t>()); /// tag

            auto&& measurement = static_cast<SR_UTILS_NS::Measurement>(marshal.Read<uint8_t>()); /// measurement

            if (measurement == SR_UTILS_NS::Measurement::Space2D) {
                migrated.Write<uint64_t>(53);
            }
            else {
                migrated.Write<uint64_t>(51);
            }

            migrated.Write<uint16_t>(1000); /// version
            migrated.Write<uint8_t>(static_cast<uint8_t>(measurement)); /// measurement

            switch (measurement) {
                case SR_UTILS_NS::Measurement::Space2D: {
                    migrated.Write<uint8_t>(static_cast<uint8_t>(marshal.Read<uint32_t>())); /// stretch
                    migrated.Write<uint8_t>(static_cast<uint8_t>(SR_UTILS_NS::Anchor::None)); /// anchor
                    SR_FALLTHROUGH;
                }
                case SR_UTILS_NS::Measurement::Space3D:
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(0.f)), SR_MATH_NS::FVector3(0.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(0.f)), SR_MATH_NS::FVector3(0.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(1.f)), SR_MATH_NS::FVector3(1.f));
                    migrated.Write<SR_MATH_NS::FVector3>(marshal.Read<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3(1.f)), SR_MATH_NS::FVector3(1.f));
                    break;
                default:
                    break;
            }

            /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(GAME_OBJECT_HASH_NAME, 1008, 1009, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());
            /// --------------------------------------------------------------------------------------------------------

            if (marshal.Read<bool>()) { /// is prefab
                migrated.Write<bool>(true);  /// is prefab

                migrated.Write(marshal.Read<std::string>()); /// prefabPath
                migrated.Write(marshal.Read<std::string>()); /// objectName
                marshal.Read<uint64_t>(); /// tag
                //migrated.Write(marshal.Read<uint64_t>()); /// tag
                //migrated.Write<uint64_t>(SR_UTILS_NS::LayerManager::Instance().GetDefaultLayer().GetHash()); /// layer

                /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
                migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

                marshal.SetData(migrated.Stream::View(), migrated.Size());
                marshal.SetPosition(position);

                return true;
            }
            else {
                migrated.Write<bool>(false);  /// is prefab
            }

            migrated.Write<bool>(marshal.Read<bool>()); /// enabled
            migrated.Write<std::string>(marshal.Read<std::string>()); /// name
            migrated.Write<uint64_t>(marshal.Read<uint64_t>()); /// tag
            migrated.Write<uint64_t>(SR_UTILS_NS::LayerManager::Instance().GetDefaultLayer().GetHash()); /// layer

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

        static const auto CAMERA_HASH_NAME = SR_HASH_STR("Camera");
        SR_UTILS_NS::Migration::Instance().RegisterMigrator(CAMERA_HASH_NAME, 1001, 1002, [](SR_HTYPES_NS::Marshal& marshal) -> bool {
            SR_HTYPES_NS::Marshal migrated;

            uint64_t position = marshal.GetPosition();

            migrated.Stream::Write(marshal.Stream::View(), marshal.GetPosition());
            /// --------------------------------------------------------------------------------------------------------

            migrated.Write<std::string>(std::string()); /// render technique path

            /// -------------------- меня наняли дублировать длинные строки потому что я люблю большие длинные прямые комментарии, состоящие исключительно из тире.
            migrated.Stream::Write(marshal.Stream::View() + marshal.GetPosition(), marshal.Size() - marshal.GetPosition());

            marshal.SetData(migrated.Stream::View(), migrated.Size());
            marshal.SetPosition(position);

            return true;
        });

        return true;
    }
}
