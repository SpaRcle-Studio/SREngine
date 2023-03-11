//
// Created by Monika on 24.05.2022.
//

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/ResourceManager/ResourceManager.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    SR_REGISTER_COMPONENT(Behaviour);

    Behaviour::Behaviour()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(Behaviour), true /** auto remove */)
        , SR_UTILS_NS::Component()
    { }

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

    SR_HTYPES_NS::Marshal::Ptr Behaviour::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        auto&& properties = GetProperties();

        /// TODO: use unicode
        pMarshal->Write(GetResourcePath().ToString());
        pMarshal->Write<uint16_t>(properties.size());

        for (auto&& propertyId : properties) {
            pMarshal->Write<std::string>(propertyId);
            pMarshal->Write<std::any>(GetProperty(propertyId));
        }

        return pMarshal;
    }

    Behaviour* Behaviour::Load(SR_UTILS_NS::Path path) {
        SR_GLOBAL_LOCK

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        path = path.RemoveSubPath(resourceManager.GetResPath());

        if (path.IsAbs()) {
            SR_ERROR("Behaviour::Load() : the behavior cannot be located outside of the resources folder! \n\tPath: " + path.ToString());
            return nullptr;
        }

        Behaviour* pBehaviour = nullptr;

        if (path.GetExtensionView() == "cpp") {
            pBehaviour = new EvoBehaviour();
        }
        else {
            SR_WARN("Behaviour::Load() : unknown behaviour extension! Load default... \n\tExtension: \"" + path.GetExtension() + "\"");
            return new Behaviour();
        }

        pBehaviour->SetId(path, false /** auto register */);

        if (!pBehaviour->Load()) {
            SR_WARN("Behaviour::Load() : failed to load behaviour! \n\tPath: " + path.ToString());
        }

        /// отложенная ручная регистрация
        resourceManager.RegisterResource(pBehaviour);

        return pBehaviour;
    }

    void Behaviour::OnDestroy() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        Component::OnDestroy();

        RemoveUsePoint();
    }

    bool Behaviour::IsEmpty() const {
        return GetResourceId() == EMPTY_ID;
    }

    bool Behaviour::Reload() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        SR_LOG("Behaviour::Reload() : reloading \"" + std::string(GetResourceId()) + "\" behaviour...");

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

    void Behaviour::OnLoaded() {
        AddUsePoint();

        Component::OnLoaded();
    }

    void Behaviour::OnAttached() {
        Component::OnAttached();
    }

    SR_UTILS_NS::Component *Behaviour::CopyComponent() const {
        return Behaviour::Load(GetResourcePath());
    }
}