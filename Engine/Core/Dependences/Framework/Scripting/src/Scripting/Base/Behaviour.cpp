//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoBehaviour.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_SCRIPTING_NS {
    Behaviour::Behaviour()
        : IResource(typeid(Behaviour).name(), true /** auto remove */)
        , SR_UTILS_NS::Component()
    {
        Component::InitComponent<Behaviour>();
    }

    SR_UTILS_NS::Component* Behaviour::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        auto&& path = marshal.Read<std::string>();
        auto&& propertyCount = marshal.Read<uint16_t>();

        auto&& pBehaviour = Load(path);

        if (pBehaviour) {
            for (uint16_t i = 0; i < propertyCount; ++i) {
                auto&& propertyId = marshal.Read<std::string>();
                auto&& property = marshal.Read<std::any>();
                pBehaviour->SetProperty(propertyId, property);
            }
        }

        return pBehaviour;
    }

    SR_HTYPES_NS::Marshal Behaviour::Save(SR_UTILS_NS::SavableFlags flags) const {
        SR_HTYPES_NS::Marshal marshal = Component::Save(flags);

        auto&& properties = GetProperties();

        /// TODO: use unicode
        marshal.Write(GetResourcePath().ToString());
        marshal.Write<uint16_t>(properties.size());

        for (auto&& propertyId : properties) {
            marshal.Write<std::string>(propertyId);
            marshal.Write<std::any>(GetProperty(propertyId));
        }

        return marshal;
    }

    Behaviour *Behaviour::Load(SR_UTILS_NS::Path path) {
        SR_GLOBAL_LOCK

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        path = path.RemoveSubPath(resourceManager.GetResPath());

        if (path.IsAbs()) {
            SR_ERROR("Behaviour::Load() : the behavior cannot be located outside of the resources folder! \n\tPath: " + path.ToString());
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
            SR_WARN("Behaviour::Load() : failed to load behaviour! \n\tPath: " + path.ToString());
        }

        /// отложенная ручная регистрация
        resourceManager.RegisterResource(pBehaviour);

        return pBehaviour;
    }

    SR_UTILS_NS::GameObject::Ptr Behaviour::GetGameObject() const {
        if (auto&& pParent = GetParent()) {
            return pParent->GetThis();
        }

        return SR_UTILS_NS::GameObject::Ptr();
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
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SR_LOG("Behaviour::Reload() : reloading \"" + GetResourceId() + "\" behaviour...");

        m_loadState = LoadState::Reloading;

        auto&& stash = Stash();

        Unload();

        if (!Load()) {
            PopStash(stash);
            return false;
        }

        ApplyStash(stash);
        PopStash(stash);

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }

    SR_UTILS_NS::Path Behaviour::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetResPath();
    }

    SR_HTYPES_NS::DataStorage Behaviour::Stash() {
        SR_HTYPES_NS::DataStorage storage;

        auto&& props = ValueProperties();

        for (auto&& propertyId : GetProperties()) {
            props.emplace_back(std::make_pair(
                propertyId,
                GetProperty(propertyId)
            ));
        }

        storage.SetValue(props);

        return storage;
    }

    void Behaviour::ApplyStash(const SR_HTYPES_NS::DataStorage& data) {
        for (auto&& [propertyId, value] : data.GetValue<ValueProperties>()) {
            SetProperty(propertyId, value);
        }
    }

    void Behaviour::PopStash(const SR_HTYPES_NS::DataStorage& data) {
        /** nothing */
    }

    void Behaviour::OnAttached() {
        Component::OnAttached();
    }
}