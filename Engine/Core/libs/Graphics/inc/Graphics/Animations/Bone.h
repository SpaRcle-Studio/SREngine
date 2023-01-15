//
// Created by Monika on 19.08.2021.
//

#ifndef GAMEENGINE_BONE_H
#define GAMEENGINE_BONE_H

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>

#include <Graphics/Types/Mesh.h>
#include <Graphics/Render/Render.h>

namespace SR_ANIMATIONS_NS {
    struct Bone : public SR_UTILS_NS::NonCopyable {
    public:
        ~Bone() override {
            for (auto&& pBone : bones) {
                delete pBone;
            }
        }

        SR_NODISCARD Bone* CloneRoot() const noexcept {
            Bone* pRootBone = new Bone();

            pRootBone->hashName = hashName;
            pRootBone->name = name;
            pRootBone->gameObject = gameObject;
            pRootBone->pRoot = pRootBone;
            pRootBone->pParent = nullptr;
            pRootBone->pScene = pScene;

            pRootBone->bones.reserve(bones.size());

            for (auto&& pSubBone : bones) {
                pRootBone->bones.emplace_back(pSubBone->Clone(pRootBone));
            }

            return pRootBone;
        }

        bool Initialize() {
            if (!pRoot->gameObject && !pRoot->pScene) {
                SRHalt0();
                hasError = true;
                return false;
            }

            std::vector<uint64_t> names = { hashName };

            Bone* pParentBone = pParent;
            /// рутовую ноду в расчет не берем
            while (pParentBone && pParentBone->pParent) {
                names.emplace_back(pParentBone->hashName);
                pParentBone = pParentBone->pParent;
            }

            if (pRoot->gameObject) {
                gameObject = pRoot->gameObject;
            }

            for (int32_t i = names.size() - 1; i >= 0; i--) {
                if (gameObject) {
                    if (!(gameObject = gameObject->Find(names[i]))) {
                        break;
                    }
                }
                else {
                    if (!(gameObject = pRoot->pScene->Find(names[i]))) {
                        break;
                    }
                }
            }

            hasError = !gameObject.Valid();

            return !hasError;
        }

    private:
        SR_NODISCARD Bone* Clone(Bone* pParentBone) const noexcept {
            Bone* pBone = new Bone();

            pBone->hashName = hashName;
            pBone->name = name;
            pBone->gameObject = gameObject;
            pBone->pParent = pParentBone;
            pBone->pRoot = pParentBone->pRoot;
            pBone->pScene = pParentBone->pScene;

            pBone->bones.reserve(bones.size());

            for (auto&& pSubBone : bones) {
                pBone->bones.emplace_back(pSubBone->Clone(pBone));
            }

            return pBone;
        }

    public:
        uint64_t hashName = 0;
        std::string name;
        SR_WORLD_NS::Scene* pScene = nullptr;
        SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject> gameObject;
        std::vector<Bone*> bones;
        Bone* pParent = nullptr;
        Bone* pRoot = nullptr;
        bool hasError = false;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    /// Ключевой кадр с позицией кости
    struct BoneAnimationPositionFrame {
        float time; // номер кадра
        glm::vec3 position; // позиция относительно родительской кости
    };

    /// Ключевой кадр с ориентацией кости
    struct BoneAnimationOrientationFrame {
        float time; // номер кадра
        glm::quat orientation; // ориентация относительно родительской кости
    };

    /// Набор ключевых кадров отдельной кости
    struct BoneAnimationChannel {
        std::vector<BoneAnimationPositionFrame> positionFrames;
        std::vector<BoneAnimationOrientationFrame> orientationFrames;
    };

    struct BonePose {
        BonePose() = default;

        BonePose(glm::vec3& position, glm::quat& orientation, float_t scale)
            : m_position(position)
            , m_orientation(orientation)
            , m_scale(scale)

        {
        }

        SR_NODISCARD glm::mat4 getBoneMatrix() const
        {
            return glm::translate(glm::identity<glm::mat4>(), m_position) * glm::mat4_cast(m_orientation);
        }

        float_t m_scale = 0.f;
        glm::quat m_orientation = glm::identity<glm::quat>();
        glm::vec3 m_position = glm::vec3(0.0f);
    };


    class SR_DEPRECATED BoneComponent : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);

        SR_INITIALIZE_COMPONENT(BoneComponent);


        ~BoneComponent() override = default;

    public:
        BoneComponent(uint32_t parentId, const glm::mat4& inverseBindPoseMatrix);


    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
            return nullptr;
        }

        void OnDestroy() override {

            delete this;
        }
    public:
        std::string m_name; // Название кости
        uint32_t parentId; // ID родительской кости (для корневой кости будем зарезервируем идентификатор ROOT_BONE_PARENT_ID)
        uint32_t m_parentId; // ID родительской кости
        glm::mat4 m_inverseBindPoseMatrix; // обратная bind-pose матрица для перехода в систему координат кости из пространства модели
        BonePose m_pose; // текущая поза кости

        static constexpr uint32_t ROOT_BONE_PARENT_ID = UINT32_MAX; // ID корневой кости
    };
}

#endif //GAMEENGINE_BONE_H
