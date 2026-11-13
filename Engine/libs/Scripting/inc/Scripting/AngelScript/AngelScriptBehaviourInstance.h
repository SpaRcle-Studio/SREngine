//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BEHAVIOUR_INSTANCE_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BEHAVIOUR_INSTANCE_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/Base/BehaviourInstance.h>
#include <Scripting/AngelScript/AngelScriptBindings.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Types/Map.h>

namespace SR_SCRIPTING_NS {
    class AngelScriptRuntime;

    class SR_SCRIPTING_DLL_API AngelScriptBehaviourInstance final : public BehaviourInstance, public SR_UTILS_NS::SRClass {
    public:
        enum class Callback : uint32_t {
            Awake,
            Start,
            OnEnable,
            OnDisable,
            OnAttached,
            OnDetached,
            OnDestroy,
            FixedUpdate,
            Update,
            ExecuteInEditMode,
            OnCollisionEnter,
            OnCollisionStay,
            OnCollisionExit,
            OnTriggerEnter,
            OnTriggerStay,
            OnTriggerExit,
            Count
        };

    public:
        class Meta final : public SR_UTILS_NS::SRClassMeta {
        public:
            SR_UTILS_NS::StringAtom name;
            SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::Property> properties;
            SR_UTILS_NS::StringAtom GetFactoryName() const noexcept override {
                return name;
            }

            std::span<const SR_UTILS_NS::Reflection::Property> GetProperties() const noexcept override {
                return { properties.data(), properties.size() };
            }
        };

        AngelScriptBehaviourInstance(AngelScriptRuntime* pSystem, SR_UTILS_NS::StringAtom name);
        ~AngelScriptBehaviourInstance() override;

    public:
        bool IsValid() const override { return m_pObject != nullptr; }
        const SR_UTILS_NS::SRClassMeta* GetMeta() const noexcept override { return &m_meta; }
        SR_UTILS_NS::StringAtom GetBehaviourName() const { return m_name; }

        bool ExecuteInEditMode() const override;

        SR_UTILS_NS::SRClass* GetPropertiesObject() const override {
            return m_pObject ? const_cast<AngelScriptBehaviourInstance*>(this) : nullptr;
        }

        void SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& object) override;
        void Save(SR_UTILS_NS::ISerializer& serializer) const override;
        bool Load(SR_UTILS_NS::IDeserializer& deserializer) override;

        void SetInstance(asIScriptObject* pObject);
        bool Invoke(Callback callback, const void* pArgument = nullptr, bool floating = false, bool* pReturnValue = nullptr) const;

    public:
        void Awake() override {
            Invoke(Callback::Awake);
        }

        void Start() override {
            Invoke(Callback::Start);
        }

        void OnEnable() override {
            Invoke(Callback::OnEnable);
        }

        void OnDisable() override {
            Invoke(Callback::OnDisable);
        }

        void OnAttached() override {
            Invoke(Callback::OnAttached);
        }

        void OnDetached() override {
            Invoke(Callback::OnDetached);
        }

        void OnDestroy() override {
            Invoke(Callback::OnDestroy);
        }

        void FixedUpdate() override {
            Invoke(Callback::FixedUpdate);
        }

        void Update(float_t dt) override {
            Invoke(Callback::Update, &dt, true);
        }

        void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) override;

    private:
        void RefreshProperties();
        void CacheCallbacks();
        static bool IsSceneField(const char* pName);
        static bool IsConstField(asIScriptObject* pObject, uint32_t index);
        void InvokeCollision(Callback callback, const SR_UTILS_NS::CollisionData& data);

    private:
        AngelScriptRuntime* m_pRuntime = nullptr;
        SR_UTILS_NS::StringAtom m_name;
        SR_UTILS_NS::SceneObject::Ptr m_sceneObject;
        asIScriptObject* m_pObject = nullptr;
        SR_UTILS_NS::Map<SR_UTILS_NS::StringAtom, SR_UTILS_NS::Reflection::Value> m_reloadValues;
        SR_UTILS_NS::Map<SR_UTILS_NS::StringAtom, SR_UTILS_NS::String> m_reloadTypes;
        Meta m_meta;

        mutable SR_UTILS_NS::Vector<asIScriptContext*> m_contexts;
        mutable uint32_t m_contextDepth = 0;
        asIScriptFunction* m_pMethods[static_cast<uint32_t>(Callback::Count)] = {};
        bool m_typedCollisions[6] = {};
        bool m_sceneFieldsInitialized = false;
    };
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BEHAVIOUR_INSTANCE_H
