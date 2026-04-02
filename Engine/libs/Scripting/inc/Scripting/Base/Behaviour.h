//
// Created by Monika on 24.05.2022.
//

#ifndef SR_ENGINE_SCRIPTING_BEHAVIOUR_H
#define SR_ENGINE_SCRIPTING_BEHAVIOUR_H

#include <Scripting/Cpp/ModuleManager.h>

#include <Utils/ECS/Component.h>
#include <Utils/Resources/IResource.h>
#include <Utils/Serialization/BaseSerialization.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Transform3D;
    class Transform;
}

namespace SR_SCRIPTING_NS {
    class ScriptSystem;
    class CppBehaviourInstance;
    class CppBehaviour;
    class Behaviour;

    /// @category(Scripting) @inspector(BehaviourPropertyDrawer)
    class Behaviour final : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Save(SR_UTILS_NS::ISerializer& serializer) const override;
        bool Load(SR_UTILS_NS::IDeserializer& deserializer) override;

        SR_NODISCARD bool IsInstanceValid() const noexcept;
        SR_NODISCARD bool ExecuteInEditMode() const override;

        template<typename T = CppBehaviour> T* GetBehaviour() {
            SR_TRACY_ZONE;
            if (!m_cppBehaviour) {
                return nullptr;
            }

            if constexpr (std::is_same_v<T, CppBehaviour>) {
                return m_cppBehaviour->GetBehaviour().Get();
            }
            else {
                auto&& pBehaviour = m_cppBehaviour->GetBehaviour().Get();
                if (pBehaviour->GetMeta()->IsSameOrInherited(T::GetClassStaticName())) {
                    return static_cast<T*>(pBehaviour);
                }
                return nullptr;
            }
        }

        void SetBehaviourName(SR_UTILS_NS::StringAtom name);

    private:
        void Awake() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDetached() override;
        void OnDestroy() override;
        void Start() override;
        void Update(float_t dt) override;
        void FixedUpdate() override;

        void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) override;

    private:
        void OnBehaviourPreReload();
        void OnBehaviourLoaded();
        void TryLoadBehaviourData();

    private:
        CppBehaviourInstance* m_cppBehaviour = nullptr;
        std::optional<SR_UTILS_NS::SerializationNode> m_serializationNode;

        /// @property @setter(SetBehaviourName) @inspector(BehaviourNamePropertyDrawer)
        SR_UTILS_NS::StringAtom m_behaviourName;

    };
}

#endif //SR_ENGINE_BEHAVIOUR_H
