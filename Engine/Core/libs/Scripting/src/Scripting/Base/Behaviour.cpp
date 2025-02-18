//
// Created by Monika on 24.05.2022.
//

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Resources/ResourceManager.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoBehaviour.h>

#include <Codegen/Behaviour.generated.hpp>

namespace SR_SCRIPTING_NS {
    IRawBehaviour* IRawBehaviour::Load(SR_UTILS_NS::Path path) {
        SR_GLOBAL_LOCK

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        path = path.RemoveSubPath(resourceManager.GetResPath());

        if (path.IsAbs()) {
            SR_ERROR("IRawBehaviour::Load() : the behavior cannot be located outside of the resources folder! \n\tPath: " + path.ToString());
            return nullptr;
        }

        IRawBehaviour* pBehaviour = nullptr;

        if (path.GetExtensionView() == "cpp") {
            pBehaviour = new EvoBehaviour();
        }
        else {
            SR_WARN("IRawBehaviour::Load() : unknown behaviour extension!\n\tExtension: \"{}\"", path.GetExtension());
            return nullptr;
        }

        pBehaviour->SetId(path.ToStringRef(), false /** auto register */);

        if (!pBehaviour->Load()) {
            SR_WARN("Behaviour::Load() : failed to load behaviour! \n\tPath: " + path.ToString());
        }

        /// отложенная ручная регистрация
        resourceManager.RegisterResource(pBehaviour);

        return pBehaviour;
    }

    bool IRawBehaviour::Reload() {
        SRHalt("Is not reloadeable! Use group reloader.");
        return false;
    }

    void IRawBehaviour::OnReloadDone() {
        m_component->OnBehaviourChanged();
        IResource::OnReloadDone();
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void Behaviour::Awake() {
        if (m_rawBehaviour) { m_rawBehaviour->Awake(); }
        Super::Awake();
    }

    void Behaviour::OnEnable() {
        if (m_rawBehaviour) { m_rawBehaviour->OnEnable(); }
        Super::OnEnable();
    }

    void Behaviour::OnDisable() {
        if (m_rawBehaviour) { m_rawBehaviour->OnDisable(); }
        Super::OnDisable();
    }

    void Behaviour::Start() {
        if (m_rawBehaviour) { m_rawBehaviour->Start(); }
        Super::Start();
    }

    void Behaviour::OnDestroy() {
        if (m_rawBehaviour) { m_rawBehaviour->OnDestroy(); }

        SetRawBehaviour(SR_UTILS_NS::Path());

        Super::OnDestroy();

        AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void Behaviour::OnAttached() {
        if (m_rawBehaviour) { m_rawBehaviour->OnAttached(); }
        Super::OnAttached();
    }

    void Behaviour::OnDetached() {
        if (m_rawBehaviour) { m_rawBehaviour->OnDetached(); }
        Super::OnDetached();
    }

    void Behaviour::Update(float_t dt) {
        if (m_rawBehaviour) { m_rawBehaviour->Update(dt); }
        Super::Update(dt);
    }

    void Behaviour::FixedUpdate() {
        if (m_rawBehaviour) { m_rawBehaviour->FixedUpdate(); }
        Super::FixedUpdate();
    }

    void Behaviour::OnTransformSet() {
        if (m_rawBehaviour) { m_rawBehaviour->OnTransformSet(); }
        Super::OnTransformSet();
    }

    void Behaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) {
        if (m_rawBehaviour) { m_rawBehaviour->OnCollisionEnter(data); }
        Super::OnCollisionEnter(data);
    }

    void Behaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData& data) {
        if (m_rawBehaviour) { m_rawBehaviour->OnCollisionExit(data); }
        Super::OnCollisionExit(data);
    }

    void Behaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData& data) {
        if (m_rawBehaviour) { m_rawBehaviour->OnCollisionStay(data); }
        Super::OnCollisionStay(data);
    }

    void Behaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) {
        if (m_rawBehaviour) { m_rawBehaviour->OnTriggerEnter(data); }
        Super::OnTriggerEnter(data);
    }

    void Behaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData& data) {
        if (m_rawBehaviour) { m_rawBehaviour->OnTriggerExit(data); }
        Super::OnTriggerExit(data);
    }

    void Behaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData& data) {
        if (m_rawBehaviour) { m_rawBehaviour->OnTriggerStay(data); }
        Super::OnTriggerStay(data);
    }

    SR_UTILS_NS::Path Behaviour::GetRawBehaviourPath() const noexcept {
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
        if (m_rawBehaviour) {
            m_rawBehaviour->SetComponent(this);
        }

        /// чтобы скрипт занаво отработал логику после перезагрузки,
        /// делаем такой маневр
        m_isStarted = false;
        m_isAwake = false;

        if (HasParent()) {
            GetParent()->SetDirty(true);
        }
    }

    void Behaviour::Save(SR_UTILS_NS::ISerializer& serializer) const {
        Super::Save(serializer);

        if (m_rawBehaviour) {
            auto&& properties = m_rawBehaviour->GetProperties();

            serializer.BeginArray(properties.size(), SR_UTILS_NS::SerializationId::Create("properties"));

            for (auto&& propertyId : properties) {
                serializer.BeginItem(SR_UTILS_NS::SerializationId::Create("property"));

                serializer.WriteString(propertyId, SR_UTILS_NS::SerializationId::Create("id"));
                serializer.WriteAny(m_rawBehaviour->GetProperty(propertyId), SR_UTILS_NS::SerializationId::Create("value"));

                serializer.EndItem();
            }

            serializer.EndArray();
        }
    }

    void Behaviour::Load(SR_UTILS_NS::IDeserializer& deserializer) {
        Super::Load(deserializer);

        if (!m_rawBehaviour) {
            return;
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
        }
    }

    void Behaviour::Reload() {
        SetRawBehaviour(m_rawBehaviour->GetResourcePath());
    }
}