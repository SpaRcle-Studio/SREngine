//
// Created by Monika on 12.12.2022.
//

#include <Utils/ECS/IComponentable.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneBuilder.h>

namespace SR_UTILS_NS {
    IComponentable::~IComponentable() {
        SRAssert(m_components.empty());
        SRAssert(m_loadedComponents.empty());
    }

    bool IComponentable::IsDirty() const noexcept {
        return m_dirty > 0;
    }

    SR_HTYPES_NS::Marshal::Ptr IComponentable::SaveComponents(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const {
        if (!pMarshal) {
            pMarshal = new SR_HTYPES_NS::Marshal();
        }

        pMarshal->Write(static_cast<uint16_t>(m_components.size() + m_loadedComponents.size()));

        for (auto&& pComponent : m_components) {
            auto&& marshalComponent = pComponent->Save(nullptr, flags);
            pMarshal->Write<uint32_t>(marshalComponent->Size());
            pMarshal->Append(marshalComponent);
        }

        for (auto&& pComponent : m_loadedComponents) {
            auto&& marshalComponent = pComponent->Save(nullptr, flags);
            pMarshal->Write<uint32_t>(marshalComponent->Size());
            pMarshal->Append(marshalComponent);
        }

        return pMarshal;
    }

    Component* IComponentable::GetComponent(const std::string& name) {
        return GetComponent(SR_HASH_STR(name));
    }

    bool IComponentable::ContainsComponent(const std::string& name) {
        return GetComponent(name);
    }

    Component* IComponentable::GetOrCreateComponent(const std::string& name) {
        if (auto&& pComponent = GetComponent(name)) {
            return pComponent;
        }

        if (auto&& pComponent = ComponentManager::Instance().CreateComponentOfName(name)) {
            if (AddComponent(pComponent)) {
                return pComponent;
            }
            else {
                SRHalt("IComponentable::GetOrCreateComponent() : failed to add component!");
            }
        }

        return nullptr;
    }

    Component* IComponentable::GetComponent(size_t hashName) {
        for (auto&& pComponent : m_components) {
            if (pComponent->GetComponentHashName() != hashName) {
                continue;
            }

            return pComponent;
        }

        return nullptr;
    }

    void IComponentable::ForEachComponent(const std::function<bool(Component *)> &fun) {
        for (auto&& component : m_components) {
            if (!fun(component)) {
                break;
            }
        }
    }

    bool IComponentable::AddComponent(Component* pComponent) {
        if (!pComponent) {
            SRHalt("pComponent is nullptr!");
            return false;
        }

        m_loadedComponents.emplace_back(pComponent);

        pComponent->OnLoaded();

        /// pComponent->OnAttached();
        /// Здесь нельзя аттачить, иначе будет очень трудно отлавливаемый deadlock и много других проблем

        SetDirty(true);

        return true;
    }

    bool IComponentable::RemoveComponent(Component *pComponent) {
        auto&& pIt = std::find(m_components.begin(), m_components.end(), pComponent);

        if (pIt == m_components.end()) {
            auto&& pLoadedIt = std::find_if(m_loadedComponents.begin(), m_loadedComponents.end(), [&](auto&& pElement) {
                return pComponent == pElement;
            });

            if (pLoadedIt == m_loadedComponents.end()) {
                SR_ERROR("IComponentable::RemoveComponent() : component \"" + pComponent->GetComponentName() + "\" not found!");
                return false;
            }
            else {
                m_loadedComponents.erase(pLoadedIt);
            }
        }
        else {
            m_components.erase(pIt);
        }

        if (pComponent->GetParent() != this) {
            SRHalt("Game object not are children!");
        }

        DestroyComponent(pComponent);

        return true;
    }

    bool IComponentable::PostLoad() {
        if (!IsDirty()) {
            return false;
        }

        if (!m_loadedComponents.empty()) {
            SRAssert2(GetScene(), "Missing scene!");

            m_components.reserve(m_loadedComponents.size());

            for (auto&& pLoadedCmp : m_loadedComponents) {
                m_components.emplace_back(pLoadedCmp);

                pLoadedCmp->SetParent(this);

                pLoadedCmp->OnAttached();
                pLoadedCmp->OnMatrixDirty();
            }

            m_loadedComponents.clear();
        }

        return true;
    }

    void IComponentable::Awake(bool isPaused) noexcept {
        if (!IsDirty()) {
            return;
        }

        for (uint32_t i = 0; i < m_components.size(); ++i) {
            auto&& pComponent = m_components[i];

            if (isPaused && !pComponent->ExecuteInEditMode()) {
                continue;
            }

            if (pComponent->IsAwake()) {
                continue;
            }

            pComponent->Awake();
        }
    }

    void IComponentable::Start() noexcept {
        if (!IsDirty()) {
            return;
        }

        for (uint32_t i = 0; i < m_components.size(); ++i) {
            auto&& pComponent = m_components[i];

            if (!pComponent->IsAwake()) {
                continue;
            }

            if (pComponent->IsStarted()) {
                continue;
            }

            pComponent->Start();
        }
    }

    void IComponentable::CheckActivity() noexcept {
        if (!IsDirty()) {
            return;
        }

        for (uint32_t i = 0; i < m_components.size(); ++i) {
            auto&& pComponent = m_components[i];

            if (!pComponent->IsAwake()) {
                continue;
            }

            pComponent->CheckActivity();
        }
    }

    void IComponentable::DestroyComponents() {
        for (uint32_t i = 0; i < m_components.size(); ++i) {
            auto&& pComponent = m_components[i];
            DestroyComponent(pComponent);
        }

        for (auto&& pComponent : m_loadedComponents) {
            DestroyComponent(pComponent);
        }

        m_loadedComponents.clear();
        m_components.clear();
    }

    void IComponentable::DestroyComponent(Component* pComponent) {
        if (auto&& pScene = GetScene()) {
            pScene->Remove(pComponent);
        }
        else {
            pComponent->OnDestroy();
        }
        SetDirty(true);
    }

    IComponentable::ScenePtr IComponentable::GetScene() const {
        SRHalt("Not implemented!");
        return nullptr;
    }
}