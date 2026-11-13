//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Base/ScriptSystem.h>

#include <Utils/Common/Bind.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/World/Scene.h>
#include <Utils/Serialization/SRASerialization.h>
#include <Utils/Events/Broadcaster.h>

#include <Codegen/Behaviour.generated.hpp>

namespace SR_SCRIPTING_NS {
    void Behaviour::Awake() {
        if (m_behaviourInstance) {
            m_behaviourInstance->Awake();
        }
        Super::Awake();
    }

    void Behaviour::OnEnable() {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnEnable();
        }
        Super::OnEnable();
    }

    void Behaviour::OnDisable() {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnDisable();
        }
        Super::OnDisable();
    }

    void Behaviour::Start() {
        if (m_behaviourInstance) {
            m_behaviourInstance->Start();
        }
        Super::Start();
    }

    void Behaviour::OnDestroy() {
        m_scriptTypesSubscription.Reset();
        if (m_behaviourInstance) {
            m_behaviourInstance->OnDestroy();
        }

        SetBehaviourName(SR_UTILS_NS::StringAtom());

        Super::OnDestroy();
    }

    void Behaviour::OnAttached() {
        m_scriptTypesSubscription.Reset();
        m_scriptTypesSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(
            SR_UTILS_NS::Events::EVENT_ON_SCRIPT_MODULE_RELOADED_ID,
            [this](const SR_UTILS_NS::SubscriptionMessage&) { OnScriptTypesChanged(); });
        if (!m_behaviourInstance) {
            SetBehaviourName(m_behaviourName);
        }

        if (IsInstanceValid()) {
            m_behaviourInstance->SetSceneObject(GetSceneObject());
            m_behaviourInstance->OnAttached();
        }

        TryLoadBehaviourData();

        Super::OnAttached();
    }

    void Behaviour::OnDetached() {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnDetached();
        }
        Super::OnDetached();
    }

    void Behaviour::Update(float_t dt) {
        if (m_behaviourInstance) {
            m_behaviourInstance->SetSceneObject(GetSceneObject());
            m_behaviourInstance->Update(dt);
        }
        Super::Update(dt);
    }

    void Behaviour::FixedUpdate() {
        if (m_behaviourInstance) {
            m_behaviourInstance->FixedUpdate();
        }
        Super::FixedUpdate();
    }

    void Behaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnCollisionEnter(data);
        }
        Super::OnCollisionEnter(data);
    }

    void Behaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData& data) {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnCollisionExit(data);
        }
        Super::OnCollisionExit(data);
    }

    void Behaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData& data) {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnCollisionStay(data);
        }
        Super::OnCollisionStay(data);
    }

    void Behaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnTriggerEnter(data);
        }
        Super::OnTriggerEnter(data);
    }

    void Behaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData& data) {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnTriggerExit(data);
        }
        Super::OnTriggerExit(data);
    }

    void Behaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData& data) {
        if (m_behaviourInstance) {
            m_behaviourInstance->OnTriggerStay(data);
        }
        Super::OnTriggerStay(data);
    }

    void Behaviour::Save(SR_UTILS_NS::ISerializer& serializer) const {
        Super::Save(serializer);

        if (IsInstanceValid()) {
            static const auto dataId = SR_UTILS_NS::SerializationId::Create("data");
            serializer.BeginObject(dataId);
            m_behaviourInstance->Save(serializer);
            serializer.EndObject();
        }
        else if (m_serializationNode) {
            auto&& impl = dynamic_cast<SR_UTILS_NS::IBaseSerialization&>(serializer);
            impl.WriteNode(*m_serializationNode);
        }
    }

    bool Behaviour::Load(SR_UTILS_NS::IDeserializer& deserializer) {
        if (!Super::Load(deserializer)) {
            return false;
        }

        static const auto dataId = SR_UTILS_NS::SerializationId::Create("data");
        if (deserializer.BeginObject(dataId)) {
            if (IsInstanceValid()) {
                m_behaviourInstance->Load(deserializer);
                m_serializationNode.Reset();
            }
            else {
                auto&& impl = dynamic_cast<SR_UTILS_NS::IBaseSerialization&>(deserializer);
                m_serializationNode = impl.GetWalkNode().DetachAllocator();
            }
            deserializer.EndObject();
        }

        return true;
    }

    void Behaviour::SetBehaviourName(SR_UTILS_NS::StringAtom name) {
        auto&& scriptSystem = SR_SCRIPTING_NS::ScriptSystem::Instance();

        if (scriptSystem.IsInitialized()) {
            if (m_behaviourInstance) {
                scriptSystem.FreeBehaviourInstance(m_behaviourInstance);
                m_behaviourInstance = nullptr;
            }

            if (!name.empty()) {
                m_behaviourInstance = scriptSystem.AllocateBehaviourInstance(name);
                if (!m_behaviourInstance) {
                    m_behaviourName = name;
                    return;
                }
                m_behaviourInstance->SetPreReloadCallback(SR_UTILS_NS::Bind(&Behaviour::OnBehaviourPreReload, this));
                m_behaviourInstance->SetLoadedCallback(SR_UTILS_NS::Bind(&Behaviour::OnBehaviourLoaded, this));
            }
        }
        m_behaviourName = name;
    }

    bool Behaviour::IsInstanceValid() const noexcept {
        return m_behaviourInstance && m_behaviourInstance->IsValid();
    }

    void Behaviour::OnScriptTypesChanged() {
        if (IsInstanceValid() || m_behaviourName.empty()) { return; }
        auto& system = ScriptSystem::Instance();
        const auto names = system.GetBehaviourNames();
        if (std::find(names.begin(), names.end(), m_behaviourName) == names.end()) { return; }
        SetBehaviourName(m_behaviourName);
        if (IsInstanceValid()) { OnBehaviourLoaded(); }
    }

    void Behaviour::OnBehaviourLoaded() {
        m_isStarted = false;
        m_isAwake = false;

        if (IsInstanceValid()) {
            m_behaviourInstance->SetSceneObject(GetSceneObject());
        }

        TryLoadBehaviourData();

        if (HasParent()) {
            GetParent()->SetDirty(true);
        }
    }

    bool Behaviour::ExecuteInEditMode() const {
        return m_behaviourInstance && m_behaviourInstance->ExecuteInEditMode();
    }

    void Behaviour::TryLoadBehaviourData() {
        if (m_serializationNode && IsInstanceValid()) {
            SR_UTILS_NS::SRADeserializer deserializer;
            if (!deserializer.LoadFromNode(std::move(*m_serializationNode))) {
                SRHalt("Impossible situation!");
            }
            m_behaviourInstance->Load(deserializer);
            m_serializationNode.Reset();
        }
    }

    void Behaviour::OnBehaviourPreReload() {
        if (IsInstanceValid()) {
            SR_UTILS_NS::SRASerializer serializer;
            m_behaviourInstance->Save(serializer);
            m_serializationNode = serializer.GetWalkNode().DetachAllocator();
        }
    }
}
