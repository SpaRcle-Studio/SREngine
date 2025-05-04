//
// Created by Monika on 24.05.2022.
//

#ifndef SR_ENGINE_SCRIPTING_BEHAVIOUR_H
#define SR_ENGINE_SCRIPTING_BEHAVIOUR_H

#include <Scripting/macros.h>

#include <Utils/ECS/Component.h>
#include <Utils/Resources/IResource.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Transform3D;
    class Transform2D;
    class Transform;
}

namespace SR_SCRIPTING_NS {
    class ScriptSystem;
    class CppBehaviourInstance;
    class Behaviour;

    /// @category(Scripting)
    class Behaviour final : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Save(SR_UTILS_NS::ISerializer& serializer) const override;
        bool Load(SR_UTILS_NS::IDeserializer& deserializer) override;

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

        void OnTransformSet() override;

        void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) override;

        SR_NODISCARD bool ExecuteInEditMode() const override;

    private:
        void SetBehaviourName(SR_UTILS_NS::StringAtom name);
        void OnScriptReloaded();

        SR_NODISCARD ScriptSystem* GetScriptSystem() const noexcept;
        SR_NODISCARD bool IsInstanceValid() const noexcept;

    private:
        mutable ScriptSystem* m_scriptSystem = nullptr;
        CppBehaviourInstance* m_cppBehaviour = nullptr;

        /// @property @setter(SetBehaviourName)
        SR_UTILS_NS::StringAtom m_behaviourName;

        /// @virtualProperty(isInstanceValid) @dontSave @readOnly @getter(IsInstanceValid)
        SR_VIRTUAL_PROPERTY

    };
}

#endif //SR_ENGINE_BEHAVIOUR_H
