

# File Settings.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Settings.h**](Settings_8h.md)

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

    class SR_DLL_EXPORT Settings : public IResource {
    protected:
        Settings()
            : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(Settings))
        { }

        ~Settings() override = default;

    public:
        bool Destroy() final;

        void Do(const SR_HTYPES_NS::Function<void(Settings*)>& fun);

    protected:
        virtual void ClearSettings() { }
        virtual bool LoadSettings(const Xml::Node& node) { return true; }

        bool Reload() final;

    protected:
        SR_NODISCARD Path GetAssociatedPath() const override;
        SR_NODISCARD SR_XML_NS::Document LoadDocument() const;

    protected:
        bool Load() override;
        bool Unload() override;

    };

    template<typename T> class SR_DLL_EXPORT GlobalSettings : public Settings, public Singleton<T> {
        friend class Singleton<T>;
    public:
        SR_MAYBE_UNUSED static void DestroySettings() {
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

    protected:
        ~GlobalSettings() override = default;

    private:
        void OnSingletonDestroy() final;
        void InitSingleton() final;
        bool IsSingletonCanBeDestroyed() const final { return false; }
        IResource::RemoveUPResult RemoveUsePoint() final;

    };

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
}

#endif //SR_ENGINE_SETTINGS_H
```


