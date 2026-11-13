//
// Created by Codex on 13.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptBehaviourInstance.h>
#include <Scripting/AngelScript/AngelScriptRuntime.h>
#include <Scripting/AngelScript/AngelScriptValueSerialization.h>
#include <Scripting/Base/ScriptCollisionData.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/Reflection/TypeInfoSerialization.h>
#include <Utils/Serialization/Serializer.h>
#include <Utils/Serialization/Deserializer.h>

namespace SR_SCRIPTING_NS {
    bool AngelScriptBehaviourInstance::IsSceneField(const char* pName) {
        const SR_UTILS_NS::StringAtom field(pName);

        return field == "sceneObject" || field == "gameObject" || field == "transform";
    }

    bool AngelScriptBehaviourInstance::IsConstField(asIScriptObject* pObject, uint32_t index) {
        bool result = false;
        pObject->GetObjectType()->GetProperty(index, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &result);
        return result;
    }

    AngelScriptBehaviourInstance::AngelScriptBehaviourInstance(AngelScriptRuntime* pSystem, SR_UTILS_NS::StringAtom name)
        : m_pRuntime(pSystem), m_name(name)
    {
        m_meta.name = name;
    }

    AngelScriptBehaviourInstance::~AngelScriptBehaviourInstance() {
        m_meta.properties.clear();

        SRAssert2(m_contextDepth == 0, "AngelScriptBehaviourInstance::~AngelScriptBehaviourInstance() : cannot destroy an executing behaviour!");

        for (auto&& pContext : m_contexts) {
            if (pContext) {
                pContext->Release();
            }
        }

        m_contexts.clear();

        if (m_pObject) {
            m_pObject->Release();
        }
    }

    void AngelScriptBehaviourInstance::SetInstance(asIScriptObject* pObject) {
        SR_TRACY_ZONE;

        if (m_pObject) {
            m_reloadValues.clear();
            m_reloadTypes.clear();

            for (uint32_t i = 0; i < m_pObject->GetPropertyCount(); ++i) {
                if (IsSceneField(m_pObject->GetPropertyName(i)) || IsConstField(m_pObject, i)) {
                    continue;
                }

                auto value = m_pRuntime->GetBindings()->ReadProperty(m_pObject, i);

                if (value) {
                    m_reloadValues.insert(m_pObject->GetPropertyName(i), std::move(value));
                    m_reloadTypes.insert(m_pObject->GetPropertyName(i), SR_UTILS_NS::String(m_pRuntime->GetEngine()->GetTypeDeclaration(m_pObject->GetPropertyTypeId(i), true)));
                }
            }
        }

        SRAssert2(m_contextDepth == 0, "AngelScriptBehaviourInstance::SetInstance() : cannot replace an executing behaviour!");

        for (auto&& pContext : m_contexts) {
            if (pContext) {
                pContext->Release();
            }
        }

        m_contexts.clear();
        m_meta.properties.clear();

        if (m_pObject) {
            m_pObject->Release();
        }

        m_pObject = pObject;
        m_sceneFieldsInitialized = false;
        CacheCallbacks();

        if (m_pObject) {
            SetSceneObject(m_sceneObject);
            RefreshProperties();

            for (uint32_t i = 0; i < m_pObject->GetPropertyCount(); ++i) {
                if (IsConstField(m_pObject, i)) {
                    continue;
                }

                auto found = m_reloadValues.find(m_pObject->GetPropertyName(i));
                auto type = m_reloadTypes.find(m_pObject->GetPropertyName(i));

                if (found != m_reloadValues.end() && type != m_reloadTypes.end() &&
                    type->second == m_pRuntime->GetEngine()->GetTypeDeclaration(m_pObject->GetPropertyTypeId(i), true)) {
                    m_pRuntime->GetBindings()->WriteProperty(m_pObject, i, found->second);
                }
            }

            m_reloadValues.clear();
            m_reloadTypes.clear();
        }
    }

    void AngelScriptBehaviourInstance::CacheCallbacks() {
        SR_TRACY_ZONE;

        static const char* pDeclarations[] = {
            "void Awake()",
            "void Start()",
            "void OnEnable()",
            "void OnDisable()",
            "void OnAttached()",
            "void OnDetached()",
            "void OnDestroy()",
            "void FixedUpdate()",
            "void Update(float)",
            "bool ExecuteInEditMode() const",
            "void OnCollisionEnter(ScriptCollisionData@)",
            "void OnCollisionStay(ScriptCollisionData@)",
            "void OnCollisionExit(ScriptCollisionData@)",
            "void OnTriggerEnter(ScriptCollisionData@)",
            "void OnTriggerStay(ScriptCollisionData@)",
            "void OnTriggerExit(ScriptCollisionData@)",
        };

        for (uint32_t i = 0; i < static_cast<uint32_t>(Callback::Count); ++i) {
            m_pMethods[i] = m_pObject ? m_pObject->GetObjectType()->GetMethodByDecl(pDeclarations[i]) : nullptr;
        }

        if (!m_pObject) {
            return;
        }

        const auto editIndex = static_cast<uint32_t>(Callback::ExecuteInEditMode);

        if (!m_pMethods[editIndex]) {
            m_pMethods[editIndex] = m_pObject->GetObjectType()->GetMethodByDecl("bool ExecuteInEditMode()");
        }

        static const char* pCollisionDeclarations[] = {
            "void OnCollisionEnter()",
            "void OnCollisionStay()",
            "void OnCollisionExit()",
            "void OnTriggerEnter()",
            "void OnTriggerStay()",
            "void OnTriggerExit()",
        };

        for (uint32_t i = 0; i < 6; ++i) {
            const auto index = static_cast<uint32_t>(Callback::OnCollisionEnter) + i;
            m_typedCollisions[i] = m_pMethods[index] != nullptr;

            if (!m_pMethods[index]) {
                m_pMethods[index] = m_pObject->GetObjectType()->GetMethodByDecl(pCollisionDeclarations[i]);
            }
        }

        m_contexts.emplace_back(m_pRuntime->GetEngine()->CreateContext());
    }

    bool AngelScriptBehaviourInstance::Invoke(Callback callback, const void* pArgument, bool floating, bool* pReturnValue) const {
        SR_TRACY_ZONE;

        if (!m_pObject) {
            return false;
        }

        auto&& pMethod = m_pMethods[static_cast<uint32_t>(callback)];

        if (!pMethod) {
            return true;
        }

        if (m_contextDepth == m_contexts.size()) {
            m_contexts.emplace_back(m_pRuntime->GetEngine()->CreateContext());
        }

        asIScriptContext* pContext = m_contexts[m_contextDepth];

        if (!pContext) {
            return false;
        }

        ++m_contextDepth;

        bool result = pContext->Prepare(pMethod) >= 0 && pContext->SetObject(m_pObject) >= 0;

        if (result && pArgument) {
            result = floating ? pContext->SetArgFloat(0, *static_cast<const float_t*>(pArgument)) >= 0 :
                pContext->SetArgObject(0, const_cast<void*>(pArgument)) >= 0;
        }

        if (result) {
            result = m_pRuntime->Execute(pContext);
            if (result && pReturnValue) {
                *pReturnValue = pContext->GetReturnByte() != 0;
            }
        }

        pContext->Unprepare();

        --m_contextDepth;

        return result;
    }

    bool AngelScriptBehaviourInstance::ExecuteInEditMode() const {
        bool result = false;
        Invoke(Callback::ExecuteInEditMode, nullptr, false, &result);
        return result;
    }

    void AngelScriptBehaviourInstance::SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& object) {
        if (m_sceneFieldsInitialized && m_sceneObject == object) {
            return;
        }

        m_sceneObject = object;
        if (!m_pObject) {
            return;
        }

        m_sceneFieldsInitialized = true;

        const auto gameObject = object ? object.DynamicCast<SR_UTILS_NS::GameObject>() : SR_UTILS_NS::GameObject::Ptr();

        for (uint32_t i = 0; i < m_pObject->GetPropertyCount(); ++i) {
            const SR_UTILS_NS::StringAtom name(m_pObject->GetPropertyName(i));

            if (name == "sceneObject") {
                m_pRuntime->GetBindings()->WriteProperty(m_pObject, i, SR_UTILS_NS::Reflection::Value::Create(SR_UTILS_NS::SceneObject::Ptr(object)));
            }
            else if (name == "gameObject") {
                m_pRuntime->GetBindings()->WriteProperty(m_pObject, i, SR_UTILS_NS::Reflection::Value::Create(SR_UTILS_NS::GameObject::Ptr(gameObject)));
            }
            else if (name == "transform") {
                m_pRuntime->GetBindings()->WriteProperty(m_pObject, i, SR_UTILS_NS::Reflection::Value::Create(gameObject ? gameObject->GetTransform() : SR_UTILS_NS::Transform::Ptr()));
            }
        }
    }

    void AngelScriptBehaviourInstance::RefreshProperties() {
        SR_TRACY_ZONE;

        auto&& pBindings = m_pRuntime->GetBindings();

        for (uint32_t i = 0; i < m_pObject->GetPropertyCount(); ++i) {
            bool isPrivate = false, isProtected = false;
            m_pObject->GetObjectType()->GetProperty(i, nullptr, nullptr, &isPrivate, &isProtected);

            if (isPrivate || isProtected || IsSceneField(m_pObject->GetPropertyName(i))) {
                continue;
            }

            auto value = pBindings->ReadProperty(m_pObject, i);

            if (!value || !CanSerializeAngelScriptValue(value.GetTypeInfo())) {
                continue;
            }

            SR_UTILS_NS::Reflection::Property property;
            property.SetName(m_pObject->GetPropertyName(i));

            if (IsConstField(m_pObject, i)) {
                property.SetPublicity(SR_UTILS_NS::PropertyPublicity::ReadOnly);
            }

            property.SetDefaultValue(value.Copy());
            property.SetDynamicGetter([i](SR_UTILS_NS::SRClass* pOwner) {
                auto&& pInstance = static_cast<AngelScriptBehaviourInstance*>(pOwner);

                return pInstance->m_pRuntime->GetBindings()->ReadProperty(pInstance->m_pObject, i);
            });
            property.SetDynamicSetter([i](SR_UTILS_NS::SRClass* pOwner, const SR_UTILS_NS::Reflection::Value& changed) {
                auto&& pInstance = static_cast<AngelScriptBehaviourInstance*>(pOwner);

                if (!pInstance->m_pRuntime->GetBindings()->WriteProperty(pInstance->m_pObject, i, changed)) {
                    SR_WARN("AngelScriptBehaviourInstance::RefreshProperties() : AngelScript: incompatible property value: {}", pInstance->m_pObject->GetPropertyName(i));
                }
            });
            m_meta.properties.emplace_back(std::move(property));
        }
    }

    void AngelScriptBehaviourInstance::Save(SR_UTILS_NS::ISerializer& serializer) const {
        if (!m_pObject) {
            return;
        }

        for (uint32_t i = 0; i < m_pObject->GetPropertyCount(); ++i) {
            if (IsSceneField(m_pObject->GetPropertyName(i)) || IsConstField(m_pObject, i)) {
                continue;
            }

            auto value = m_pRuntime->GetBindings()->ReadProperty(m_pObject, i);

            if (!value || !CanSerializeAngelScriptValue(value.GetTypeInfo())) {
                continue;
            }

            const auto id = SR_UTILS_NS::SerializationId::CreateFromCStr(m_pObject->GetPropertyName(i));
            serializer.BeginObject(id);
            SR_UTILS_NS::String signature;
            SR_UTILS_NS::Reflection::SaveTypeInfo(signature, &value.GetTypeInfo());
            serializer.WriteString(signature, SR_UTILS_NS::SerializationId::Create("type"));
            serializer.WriteString(m_pRuntime->GetEngine()->GetTypeDeclaration(m_pObject->GetPropertyTypeId(i), true), SR_UTILS_NS::SerializationId::Create("scriptType"));
            SaveAngelScriptValue(value, serializer);
            serializer.EndObject();
        }
    }

    bool AngelScriptBehaviourInstance::Load(SR_UTILS_NS::IDeserializer& deserializer) {
        if (!m_pObject) {
            return false;
        }

        bool result = true;

        for (uint32_t i = 0; i < m_pObject->GetPropertyCount(); ++i) {
            if (IsSceneField(m_pObject->GetPropertyName(i)) || IsConstField(m_pObject, i)) {
                continue;
            }

            const auto id = SR_UTILS_NS::SerializationId::CreateFromCStr(m_pObject->GetPropertyName(i));

            if (!deserializer.BeginObject(id)) {
                continue;
            }

            auto value = m_pRuntime->GetBindings()->ReadProperty(m_pObject, i);
            SR_UTILS_NS::String signature, expected, scriptType;
            deserializer.ReadString(signature, SR_UTILS_NS::SerializationId::Create("type"));
            deserializer.ReadString(scriptType, SR_UTILS_NS::SerializationId::Create("scriptType"));

            if (value) {
                SR_UTILS_NS::Reflection::SaveTypeInfo(expected, &value.GetTypeInfo());
            }

            if (value && signature == expected && scriptType == m_pRuntime->GetEngine()->GetTypeDeclaration(m_pObject->GetPropertyTypeId(i), true)) {
                result &= CanSerializeAngelScriptValue(value.GetTypeInfo()) && LoadAngelScriptValue(value, deserializer) && m_pRuntime->GetBindings()->WriteProperty(m_pObject, i, value);
            }

            deserializer.EndObject();
        }

        return result;
    }

    void AngelScriptBehaviourInstance::InvokeCollision(Callback callback, const SR_UTILS_NS::CollisionData& data) {
        SR_TRACY_ZONE;

        const auto index = static_cast<uint32_t>(callback);

        if (!m_pObject || !m_pMethods[index]) {
            return;
        }

        if (m_typedCollisions[index - static_cast<uint32_t>(Callback::OnCollisionEnter)]) {
            ScriptCollisionData snapshot;
            snapshot.point = data.point;
            snapshot.impulse = data.impulse;

            auto&& pObject = m_pRuntime->GetBindings()->Wrap(SR_UTILS_NS::Reflection::Value::Create(std::move(snapshot)));

            if (pObject) {
                Invoke(callback, pObject);
                pObject->Release();
            }

            return;
        }

        Invoke(callback);
    }

    void AngelScriptBehaviourInstance::OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) {
        InvokeCollision(Callback::OnCollisionEnter, data);
    }

    void AngelScriptBehaviourInstance::OnCollisionStay(const SR_UTILS_NS::CollisionData& data) {
        InvokeCollision(Callback::OnCollisionStay, data);
    }

    void AngelScriptBehaviourInstance::OnCollisionExit(const SR_UTILS_NS::CollisionData& data) {
        InvokeCollision(Callback::OnCollisionExit, data);
    }

    void AngelScriptBehaviourInstance::OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) {
        InvokeCollision(Callback::OnTriggerEnter, data);
    }

    void AngelScriptBehaviourInstance::OnTriggerStay(const SR_UTILS_NS::CollisionData& data) {
        InvokeCollision(Callback::OnTriggerStay, data);
    }

    void AngelScriptBehaviourInstance::OnTriggerExit(const SR_UTILS_NS::CollisionData& data) {
        InvokeCollision(Callback::OnTriggerExit, data);
    }
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
