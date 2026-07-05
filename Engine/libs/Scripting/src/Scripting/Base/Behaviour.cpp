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
        if (m_cppBehaviour) {
            m_cppBehaviour->Awake();
        }
        Super::Awake();
    }

    void Behaviour::OnEnable() {
        if (m_cppBehaviour) {
            m_cppBehaviour->OnEnable();
        }
        Super::OnEnable();
    }

    void Behaviour::OnDisable() {
        if (m_cppBehaviour) {
            m_cppBehaviour->OnDisable();
        }
        Super::OnDisable();
    }

    void Behaviour::Start() {
        if (m_cppBehaviour) {
            m_cppBehaviour->Start();
        }
        Super::Start();
    }

    void Behaviour::OnDestroy() {
        if (m_cppBehaviour) {
            m_cppBehaviour->OnDestroy();
        }

        SetBehaviourName(SR_UTILS_NS::StringAtom());

        Super::OnDestroy();
    }

    void Behaviour::OnAttached() {
        if (!m_cppBehaviour) {
            SetBehaviourName(m_behaviourName);
        }

        if (IsInstanceValid()) {
            m_cppBehaviour->SetSceneObject(GetSceneObject());
            m_cppBehaviour->OnAttached();
        }

        TryLoadBehaviourData();

        Super::OnAttached();
    }

    void Behaviour::OnDetached() {
        if (m_cppBehaviour) {
            m_cppBehaviour->OnDetached();
        }
        Super::OnDetached();
    }

    void Behaviour::Update(float_t dt) {
        if (m_cppBehaviour) {
            m_cppBehaviour->SetSceneObject(GetSceneObject());
            m_cppBehaviour->Update(dt);
        }
        Super::Update(dt);
    }

    void Behaviour::FixedUpdate() {
        if (m_cppBehaviour) {
            m_cppBehaviour->FixedUpdate();
        }
        Super::FixedUpdate();
    }

    void Behaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) {
        Super::OnCollisionEnter(data);
    }

    void Behaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData& data) {
        Super::OnCollisionExit(data);
    }

    void Behaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData& data) {
        Super::OnCollisionStay(data);
    }

    void Behaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) {
        Super::OnTriggerEnter(data);
    }

    void Behaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData& data) {
        Super::OnTriggerExit(data);
    }

    void Behaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData& data) {
        Super::OnTriggerStay(data);
    }

    void Behaviour::Save(SR_UTILS_NS::ISerializer& serializer) const {
        Super::Save(serializer);

        if (IsInstanceValid()) {
            static const auto dataId = SR_UTILS_NS::SerializationId::Create("data");
            serializer.BeginObject(dataId);
            m_cppBehaviour->GetBehaviour()->Save(serializer);
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
                m_cppBehaviour->GetBehaviour()->Load(deserializer);
                m_serializationNode = std::nullopt;
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
            if (m_cppBehaviour) {
                scriptSystem.GetModuleManager()->FreeBehaviourInstance(m_cppBehaviour);
                m_cppBehaviour = nullptr;
            }

            if (!name.empty()) {
                m_cppBehaviour = scriptSystem.GetModuleManager()->AllocateBehaviourInstance(name);
                m_cppBehaviour->SetPreReloadCallback(std::bind(&Behaviour::OnBehaviourPreReload, this));
                m_cppBehaviour->SetLoadedCallback(std::bind(&Behaviour::OnBehaviourLoaded, this));
            }
        }
        m_behaviourName = name;
    }

    bool Behaviour::IsInstanceValid() const noexcept {
        return m_cppBehaviour && m_cppBehaviour->IsValid();
    }

    void Behaviour::OnBehaviourLoaded() {
        m_isStarted = false;
        m_isAwake = false;

        if (IsInstanceValid()) {
            m_cppBehaviour->SetSceneObject(GetSceneObject());
        }

        TryLoadBehaviourData();

        if (HasParent()) {
            GetParent()->SetDirty(true);
        }
    }

    bool Behaviour::ExecuteInEditMode() const {
        return m_cppBehaviour && m_cppBehaviour->ExecuteInEditMode();
    }

    void Behaviour::TryLoadBehaviourData() {
        if (m_serializationNode && IsInstanceValid()) {
            SR_UTILS_NS::SRADeserializer deserializer;
            if (!deserializer.LoadFromNode(std::move(*m_serializationNode))) {
                SRHalt("Impossible situation!");
            }
            m_cppBehaviour->GetBehaviour()->Load(deserializer);
            m_serializationNode = std::nullopt;
        }
    }

    void Behaviour::OnBehaviourPreReload() {
        if (IsInstanceValid()) {
            SR_UTILS_NS::SRASerializer serializer;
            m_cppBehaviour->GetBehaviour()->Save(serializer);
            m_serializationNode = serializer.GetWalkNode();
        }
    }
}