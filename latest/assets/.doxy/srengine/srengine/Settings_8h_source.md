

# File Settings.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Settings.h**](Settings_8h.md)

[Go to the documentation of this file](Settings_8h.md)


```C++
//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_SETTINGS_H
#define SR_ENGINE_SETTINGS_H

#include <Utils/Resources/Xml.h>
#include <Utils/Resources/IResource.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS(SettingsVarType,
        Unknown,
        Bool,
        Int32,
        UInt32,
        Float,
        FVec2,
        FVec3,
        FVec4,
        IVec2,
        IVec3,
        IVec4
    )

    class SR_COMMON_DLL_API Settings : public IResource {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Settings>;

    public:
        Settings();
        ~Settings() override;

    public:
        bool Destroy() final;
        bool Reload() final;

        void Do(const SR_HTYPES_NS::Function<void(Settings*)>& fun);
        SR_NODISCARD const SR_XML_NS::Document& GetDocument() const;
        SR_NODISCARD SR_XML_NS::Document LoadDocument() const;

    protected:
        virtual void ClearSettings();
        virtual bool LoadSettings(const Xml::Node& node);

    protected:
        SR_NODISCARD Path GetAssociatedPath() const override;

    protected:
        bool Load() override;
        bool Unload() override;

    private:
        SR_XML_NS::Document m_document;

    };

    template<typename T> class GlobalSettings : public Settings, public Singleton<T> {
        friend class Singleton<T>;
    public:
        SR_MAYBE_UNUSED static void DestroySettings();

    protected:
        ~GlobalSettings() override = default;

    private:
        void OnSingletonDestroy() final;
        void InitSingleton() final;
        bool IsSingletonCanBeDestroyed() const final;
        IResource::RemoveUPResult RemoveUsePoint() final;

    };

#ifdef SR_COMMON_DLL_EXPORTS
    template<typename T> bool GlobalSettings<T>::IsSingletonCanBeDestroyed() const { return false; }

    template<typename T> SR_MAYBE_UNUSED void GlobalSettings<T>::DestroySettings() {
        if (!Singleton<T>::IsSingletonInitialized()) {
            return;
        }

        auto&& pSettings = &Singleton<T>::Instance();

        GetSingletonManager()->Remove(T::GetStaticSingletonName());

        if (!pSettings->IsRegistered()) {
            return;
        }

        if (pSettings->RemoveUsePoint() == IResource::RemoveUPResult::Success) {
            pSettings->ForceDestroy();
        }

        ResourceManager::Instance().Synchronize(true);
    }

    template<typename T> void GlobalSettings<T>::OnSingletonDestroy() {
        Singleton<T>::OnSingletonDestroy();
    }

    template<typename T> void GlobalSettings<T>::InitSingleton() {
        SetId(InitializeResourcePath().ToString());

        AddUsePoint();

        if (!Reload()) {
            SR_ERROR("GlobalSettings<T>::InitSingleton() : failed to reload settings!");
        }

        Singleton<T>::InitSingleton();
    }

    template<typename T> IResource::RemoveUPResult GlobalSettings<T>::RemoveUsePoint() {
        SRAssert2(GetCountUses() > 0, "count use points is zero!");
        --m_countUses;
        return IResource::RemoveUPResult::Success;
    }
#endif
}

#endif //SR_ENGINE_SETTINGS_H
```


