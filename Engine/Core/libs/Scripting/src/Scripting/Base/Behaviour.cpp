//
// Created by Monika on 24.05.2022.
//

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/ResourceManager/ResourceManager.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoBehaviour.h>

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

    SR_REGISTER_COMPONENT(Behaviour);

    SR_UTILS_NS::Component* Behaviour::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        auto&& path = marshal.Read<std::string>();
        auto&& propertyCount = marshal.Read<uint16_t>();

        auto&& pBehaviour = SR_UTILS_NS::ComponentManager::Instance().CreateComponent<Behaviour>();

        if (pBehaviour) {
            pBehaviour->SetRawBehaviour(path);
        }

        for (uint16_t i = 0; i < propertyCount; ++i) {
            auto&& propertyId = marshal.Read<std::string>();
            auto&& property = marshal.Read<std::any>();
            if (pBehaviour && pBehaviour->m_rawBehaviour) {
                pBehaviour->m_rawBehaviour->SetProperty(propertyId, property);
            }
        }

        return pBehaviour;
    }

    SR_HTYPES_NS::Marshal::Ptr Behaviour::Save(SR_UTILS_NS::SavableSaveData data) const {
        auto&& pMarshal = Component::Save(data);

        auto&& properties = m_rawBehaviour ? m_rawBehaviour->GetProperties() : Properties();

        /// TODO: use unicode
        pMarshal->Write<std::string>(m_rawBehaviour ? m_rawBehaviour->GetResourcePath().ToString() : std::string());
        pMarshal->Write<uint16_t>(properties.size());

        for (auto&& propertyId : properties) {
            pMarshal->Write<std::string>(propertyId);
            pMarshal->Write<std::any>(m_rawBehaviour ? m_rawBehaviour->GetProperty(propertyId) : std::any());
        }

        return pMarshal;
    }

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

    SR_UTILS_NS::Component* Behaviour::CopyComponent() const {
        auto&& pBehaviour = SR_UTILS_NS::ComponentManager::Instance().CreateComponent<Behaviour>();

        if (pBehaviour && GetRawBehaviour()) {
            auto&& pRaw = GetRawBehaviour();
            pBehaviour->SetRawBehaviour(pRaw->GetResourcePath());

            for (uint16_t i = 0; i < pRaw->GetProperties().size(); ++i) {
                const auto propertyName = pRaw->GetProperties()[i];
                if (pBehaviour && pBehaviour->m_rawBehaviour) {
                    pBehaviour->m_rawBehaviour->SetProperty(propertyName, pRaw->GetProperty(propertyName));
                }
            }
        }

        return pBehaviour;
    }

    void Behaviour::OnBehaviourChanged() {
        if (m_rawBehaviour) {
            m_rawBehaviour->SetComponent(this);
        }

        /// чтобы скрипт занаво отработал логику после перезагрузки,
        /// делаем такой маневр
        m_isStarted = false;
        m_isAwake = false;

        if (auto&& pParent = GetParent()) {
            pParent->SetDirty(true);
        }
    }
}