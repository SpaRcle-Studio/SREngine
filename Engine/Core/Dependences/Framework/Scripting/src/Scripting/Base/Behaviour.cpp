//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoBehaviour.h>
#include <ECS/GameObject.h>
#include <ResourceManager/ResourceManager.h>

namespace SR_SCRIPTING_NS {
    Behaviour::Behaviour()
        : IResource(typeid(Behaviour).name(), true /** auto remove */)
        , SR_UTILS_NS::Component()
    {
        Component::InitComponent<Behaviour>();
    }

    Behaviour *Behaviour::Load(SR_UTILS_NS::Path path) {
        SR_GLOBAL_LOCK

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        path = path.RemoveSubPath(resourceManager.GetScriptsPath());

        if (path.IsAbs()) {
            SR_ERROR("Behaviour::Load() : the behavior cannot be located outside the resources folder! \n\tPath: " + path.ToString());
            return nullptr;
        }

        Behaviour* pBehaviour = nullptr;

        if (path.GetExtensionView().empty()) {
            pBehaviour = new EvoBehaviour();
        }
        else {
            SRHalt("Unknown behaviour extension!");
            return nullptr;
        }

        pBehaviour->SetId(path, false /** auto register */);

        if (!pBehaviour->Load()) {
            SR_ERROR("Behaviour::Load() : failed to load behaviour! \n\tPath: " + path.ToString());
            delete pBehaviour;
            return nullptr;
        }

        /// отложенная ручная регистрация
        resourceManager.RegisterResource(pBehaviour);

        return pBehaviour;
    }

    Behaviour::GameObjectPtr Behaviour::GetGameObject() const {
        if (auto&& pParent = GetParent()) {
            return pParent->GetThis();
        }

        return GameObjectPtr();
    }

    Behaviour::TransformPtr Behaviour::GetTransform() const {
        if (auto&& parent = GetParent()) {
            return parent->GetTransform();
        }

        return nullptr;
    }

    Behaviour *Behaviour::CreateEmpty() {
        auto&& pBehaviour = new Behaviour();

        pBehaviour->SetId(EMPTY_ID, false);

        if (!pBehaviour->Load()) {
            SR_ERROR("Behaviour::CreateEmpty() : failed to load behaviour!");
            delete pBehaviour;
            return nullptr;
        }

        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pBehaviour);

        return pBehaviour;
    }

    void Behaviour::OnDestroy() {
        if (!IsDestroyed() && GetCountUses() == 0 && IsEnabledAutoRemove()) {
            Destroy();
        }
        Component::OnDestroy();
    }

    bool Behaviour::IsEmpty() const {
        return GetResourceId() == EMPTY_ID;
    }

    bool Behaviour::Reload() {
        SR_LOG("Behaviour::Reload() : reloading \"" + GetResourceId() + "\" behaviour...");

        m_loadState = LoadState::Reloading;

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }

    SR_UTILS_NS::Path Behaviour::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetScriptsPath();
    }
}