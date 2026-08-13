//
// Created by Monika on 27.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_BEHAVIOUR_H
#define SR_ENGINE_SCRIPTING_CPP_BEHAVIOUR_H

#include <Scripting/macros.h>

#include <Utils/Serialization/Serializable.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>
#include <Utils/Common/CollisionData.h>

namespace SR_SCRIPTING_NS {
    /// @noCopyable @noMovable
    class CppBehaviour : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<CppBehaviour>, public SR_UTILS_NS::NonCopyable {
        SR_CLASS()
        using Super = SR_HTYPES_NS::SharedPtr<CppBehaviour>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<CppBehaviour>;

    public:
        CppBehaviour();
        ~CppBehaviour() override;

    public:
        virtual void OnMatrixDirty();
        virtual void OnPriorityChanged();
        virtual void OnTransformSet();

        virtual void OnAttached();
        virtual void OnDetached();
        virtual void OnDestroy();

        virtual void OnEnable();
        virtual void OnDisable();

        virtual void Awake();
        virtual void Start();
        virtual void Update(float_t dt);
        virtual void FixedUpdate();
        virtual void LateUpdate();

        virtual void OnBeforeLayerChanged();
        virtual void OnLayerChanged();

        virtual void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data);
        virtual void OnCollisionStay(const SR_UTILS_NS::CollisionData& data);
        virtual void OnCollisionExit(const SR_UTILS_NS::CollisionData& data);

        virtual void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data);
        virtual void OnTriggerStay(const SR_UTILS_NS::CollisionData& data);
        virtual void OnTriggerExit(const SR_UTILS_NS::CollisionData& data);

        SR_NODISCARD virtual bool ExecuteInEditMode() const { return false; }

    public:
        SR_UTILS_NS::GameObject::Ptr gameObject;
        SR_UTILS_NS::SceneObject::Ptr sceneObject;
        SR_UTILS_NS::Transform::Ptr transform;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_BEHAVIOUR_H
