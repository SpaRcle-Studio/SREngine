//
// Created by Monika on 19.08.2021.
//

#ifndef GAMEENGINE_BONE_H
#define GAMEENGINE_BONE_H

#include <Utils/ECS/Component.h>

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

            pRootBone->bones.reserve(bones.size());

            for (auto&& pSubBone : bones) {
                pRootBone->bones.emplace_back(pSubBone->Clone(pRootBone));
            }

            return pRootBone;
        }

    private:
        SR_NODISCARD Bone* Clone(Bone* pParentBone) const noexcept {
            Bone* pBone = new Bone();

            pBone->hashName = hashName;
            pBone->name = name;
            pBone->gameObject = gameObject;
            pBone->pParent = pParentBone;
            pBone->pRoot = pParentBone->pRoot;

            pBone->bones.reserve(bones.size());

            for (auto&& pSubBone : bones) {
                pBone->bones.emplace_back(pSubBone->Clone(pBone));
            }

            return pBone;
        }

    public:
        uint64_t hashName = 0;
        std::string name;
        SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject> gameObject;
        std::vector<Bone*> bones;
        Bone* pParent = nullptr;
        Bone* pRoot = nullptr;

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

        BonePose(const glm::vec3& position, const glm::quat& orientation, const float_t scale)
            : m_position(position)
            , m_orientation(orientation)
            , m_scale(scale)
        { }

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
        BoneComponent(uint8_t parentId, const glm::mat4& inverseBindPoseMatrix);

    private:
        //Types::Mesh* m_mesh = nullptr;
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
            return nullptr;
        }

        void OnDestroy() override {
           //if (m_mesh) {
           //    m_mesh->OnDestroy();
           //    m_mesh = nullptr;
           //}

            delete this;
        }
    public:
        std::string m_name; // Название кости
        uint32_t parentId; // ID родительской кости (для корневой кости будем зарезервируем идентификатор ROOT_BONE_PARENT_ID, таким образом, скелет сможет содержать не более, чем 254 кости)
        glm::mat4 inverseBindPoseMatrix; // обратная bind-pose матрица для перехода в систему координат кости из пространства модели

        static constexpr uint32_t ROOT_BONE_PARENT_ID = UINT32_MAX; // ID корневой кости
    };
}

#endif //GAMEENGINE_BONE_H
