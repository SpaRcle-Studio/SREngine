//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_BEHAVIOUR_INSTANCE_H
#define SR_ENGINE_SCRIPTING_BEHAVIOUR_INSTANCE_H

#include <Scripting/stdInclude.h>

#include <Utils/ECS/SceneObject.h>
#include <Utils/Common/CollisionData.h>
#include <Utils/Serialization/Serializable.h>

namespace SR_SCRIPTING_NS {
    class CppBehaviour;

    class SR_SCRIPTING_DLL_API BehaviourInstance {
    public:

        virtual ~BehaviourInstance() = default;

        SR_NODISCARD virtual bool IsValid() const = 0;
        SR_NODISCARD virtual bool ExecuteInEditMode() const = 0;
        SR_NODISCARD virtual CppBehaviour* GetCppBehaviour() const {
            return nullptr;
        }

        SR_NODISCARD virtual SR_UTILS_NS::SRClass* GetPropertiesObject() const = 0;
        virtual void SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject) = 0;
        virtual void Save(SR_UTILS_NS::ISerializer& serializer) const = 0;
        virtual bool Load(SR_UTILS_NS::IDeserializer& deserializer) = 0;

        void SetLoadedCallback(const SR_HTYPES_NS::Function<void()>& callback) {
            m_loadedCallback = callback;
        }

        void SetPreReloadCallback(const SR_HTYPES_NS::Function<void()>& callback) {
            m_preReloadCallback = callback;
        }

        SR_NODISCARD const SR_HTYPES_NS::Function<void()>& GetLoadedCallback() const {
            return m_loadedCallback;
        }

        SR_NODISCARD const SR_HTYPES_NS::Function<void()>& GetPreReloadCallback() const {
            return m_preReloadCallback;
        }

        virtual void Awake() = 0;
        virtual void Start() = 0;
        virtual void OnEnable() = 0;
        virtual void OnDisable() = 0;
        virtual void OnAttached() = 0;
        virtual void OnDetached() = 0;
        virtual void OnDestroy() = 0;
        virtual void FixedUpdate() = 0;
        virtual void Update(float_t dt) = 0;
        virtual void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) = 0;

    private:
        SR_HTYPES_NS::Function<void()> m_preReloadCallback;
        SR_HTYPES_NS::Function<void()> m_loadedCallback;
    };
}

#endif // SR_ENGINE_SCRIPTING_BEHAVIOUR_INSTANCE_H
