//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Cpp/ScriptSystem.h>
#include <Scripting/Cpp/ModuleManager.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/World/Scene.h>

#include <Codegen/Behaviour.generated.hpp>

namespace SR_SCRIPTING_NS {
    void Behaviour::Awake() {
        //if (m_rawBehaviour) { m_rawBehaviour->Awake(); }
        Super::Awake();
    }

    void Behaviour::OnEnable() {
        //if (m_rawBehaviour) { m_rawBehaviour->OnEnable(); }
        Super::OnEnable();
    }

    void Behaviour::OnDisable() {
        //if (m_rawBehaviour) { m_rawBehaviour->OnDisable(); }
        Super::OnDisable();
    }

    void Behaviour::Start() {
        //if (m_rawBehaviour) { m_rawBehaviour->Start(); }
        Super::Start();
    }

    void Behaviour::OnDestroy() {
        //if (m_rawBehaviour) { m_rawBehaviour->OnDestroy(); }

        SetBehaviourName(SR_UTILS_NS::StringAtom());

        Super::OnDestroy();

        AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void Behaviour::OnAttached() {
        if (!m_cppBehaviour) {
            SetBehaviourName(m_behaviourName);
        }

        //if (m_rawBehaviour) { m_rawBehaviour->OnAttached(); }
        Super::OnAttached();
    }

    void Behaviour::OnDetached() {
        //if (m_rawBehaviour) { m_rawBehaviour->OnDetached(); }
        Super::OnDetached();
    }

    void Behaviour::Update(float_t dt) {
        //if (m_rawBehaviour) { m_rawBehaviour->Update(dt); }
        Super::Update(dt);
    }

    void Behaviour::FixedUpdate() {
        //if (m_rawBehaviour) { m_rawBehaviour->FixedUpdate(); }
        Super::FixedUpdate();
    }

    void Behaviour::OnTransformSet() {
        //if (m_rawBehaviour) { m_rawBehaviour->OnTransformSet(); }
        Super::OnTransformSet();
    }

    void Behaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) {
        //if (m_rawBehaviour) { m_rawBehaviour->OnCollisionEnter(data); }
        Super::OnCollisionEnter(data);
    }

    void Behaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData& data) {
        //if (m_rawBehaviour) { m_rawBehaviour->OnCollisionExit(data); }
        Super::OnCollisionExit(data);
    }

    void Behaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData& data) {
        //if (m_rawBehaviour) { m_rawBehaviour->OnCollisionStay(data); }
        Super::OnCollisionStay(data);
    }

    void Behaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) {
        //if (m_rawBehaviour) { m_rawBehaviour->OnTriggerEnter(data); }
        Super::OnTriggerEnter(data);
    }

    void Behaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData& data) {
        //if (m_rawBehaviour) { m_rawBehaviour->OnTriggerExit(data); }
        Super::OnTriggerExit(data);
    }

    void Behaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData& data) {
        //if (m_rawBehaviour) { m_rawBehaviour->OnTriggerStay(data); }
        Super::OnTriggerStay(data);
    }

    /*SR_UTILS_NS::Path Behaviour::GetRawBehaviourPath() const noexcept {
        return m_rawBehaviour ? m_rawBehaviour->GetResourcePath() : SR_UTILS_NS::Path();
    }

    void Behaviour::SetRawBehaviour(const SR_UTILS_NS::Path& path) {
        if (m_rawBehaviour) {
            m_rawBehaviour->SetComponent(nullptr);
            m_rawBehaviour->RemoveUsePoint();
            m_rawBehaviour = nullptr;
        }

        if (!path.empty()) {
            m_rawBehaviour = IRawBehaviour::Load(path);
        }

        if (m_rawBehaviour) {
            m_rawBehaviour->AddUsePoint();
        }

        OnBehaviourChanged();
    }

     void Behaviour::OnBehaviourChanged() {
        //if (m_rawBehaviour) {
        //    m_rawBehaviour->SetComponent(this);
        //}


    }*/

    void Behaviour::Save(SR_UTILS_NS::ISerializer& serializer) const {
        Super::Save(serializer);

        /*if (m_rawBehaviour) {
            auto&& properties = m_rawBehaviour->GetProperties();

            serializer.BeginArray(properties.size(), SR_UTILS_NS::SerializationId::Create("properties"));

            for (auto&& propertyId : properties) {
                serializer.BeginItem(SR_UTILS_NS::SerializationId::Create("property"));

                serializer.WriteString(propertyId, SR_UTILS_NS::SerializationId::Create("id"));
                serializer.WriteAny(m_rawBehaviour->GetProperty(propertyId), SR_UTILS_NS::SerializationId::Create("value"));

                serializer.EndItem();
            }

            serializer.EndArray();
        }*/
    }

    bool Behaviour::Load(SR_UTILS_NS::IDeserializer& deserializer) {
        if (!Super::Load(deserializer)) {
            return false;
        }

        /*if (!m_rawBehaviour) {
            return true;
        }

        auto&& properties = m_rawBehaviour->GetProperties();

        const uint64_t size = deserializer.BeginArray(SR_UTILS_NS::SerializationId::Create("properties"));

        if (size > 0) {
            uint64_t index = 0;

            while (deserializer.BeginItem(SR_UTILS_NS::SerializationId::Create("property"), index)) {
                std::string propertyId;
                deserializer.ReadString(propertyId, SR_UTILS_NS::SerializationId::Create("id"));

                for (auto&& property : properties) {
                    if (property == propertyId) {
                        std::any value;
                        deserializer.ReadAny(value, SR_UTILS_NS::SerializationId::Create("value"));
                        m_rawBehaviour->SetProperty(property, value);
                        break;
                    }
                }

                deserializer.EndItem();
                index++;
            }

            deserializer.EndArray();
        }*/

        return true;
    }

    void Behaviour::SetBehaviourName(SR_UTILS_NS::StringAtom name) {
        if (auto&& pScriptSystem = GetScriptSystem()) {
            if (m_cppBehaviour) {
                pScriptSystem->GetModuleManager()->FreeBehaviourInstance(m_cppBehaviour);
                m_cppBehaviour = nullptr;
            }

            if (!name.empty()) {
                m_cppBehaviour = pScriptSystem->GetModuleManager()->AllocateBehaviourInstance(name);
                m_cppBehaviour->SetReloadCallback(std::bind(&Behaviour::OnScriptReloaded, this));
            }
        }
        else if (m_cppBehaviour) {
            SRHalt("Behaviour::SetBehaviourName() : script system is not available, but C++ behaviour is set!");
        }
        m_behaviourName = name;
    }

    ScriptSystem* Behaviour::GetScriptSystem() const noexcept {
        if (m_scriptSystem) {
            return m_scriptSystem;
        }

        if (auto&& pScene = TryGetScene()) {
            m_scriptSystem = pScene->GetDataStorage().GetPointer<ScriptSystem>();
        }

        return m_scriptSystem;
    }

    bool Behaviour::IsInstanceValid() const noexcept {
        return m_cppBehaviour && m_cppBehaviour->GetInstance();
    }

    void Behaviour::OnScriptReloaded() {
        m_isStarted = false;
        m_isAwake = false;

        if (HasParent()) {
            GetParent()->SetDirty(true);
        }
    }
}