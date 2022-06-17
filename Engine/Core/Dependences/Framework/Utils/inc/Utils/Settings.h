//
// Created by Monika on 17.06.2022.
//

#ifndef SRENGINE_SETTINGS_H
#define SRENGINE_SETTINGS_H

#include <Utils/Xml.h>
#include <Utils/ResourceManager/IResource.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    SR_ENUM_CLASS(SettingsVarType,
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
          IVec4,
    )

    class SR_DLL_EXPORT Settings : public IResource {
    protected:
        explicit Settings()
            : IResource(typeid(Settings).name(), true /** auto remove */)
        { }

        ~Settings() override = default;

    protected:
        virtual void ClearSettings() { }
        virtual void LoadSettings(const Xml::Node& node) { }

        bool Reload() final;
        bool Destroy() final;

    protected:
        SR_NODISCARD Path GetResourcePath() const override;
        SR_NODISCARD Path GetAssociatedPath() const override;

    private:
        bool Load() override;
        bool Unload() override;

    };

    template<typename T> class SR_DLL_EXPORT GlobalSettings : public Settings, public Singleton<T> {
        friend class Singleton<T>;
    public:
        void DestroySettings();

    protected:
        ~GlobalSettings() override = default;

    private:
        void OnSingletonDestroy() final;
        void InitSingleton() final;
        bool IsSingletonCanBeDestroyed() const final { return false; }

    };

    template<typename T> void GlobalSettings<T>::OnSingletonDestroy() {
        Singleton<T>::OnSingletonDestroy();
    }

    template<typename T> void GlobalSettings<T>::InitSingleton() {
        SetId(GetResourcePath());

        AddUsePoint();

        if (!Reload()) {
            SR_ERROR("GlobalSettings<T>::InitSingleton() : failed to reload settings!");
        }

        Singleton<T>::InitSingleton();
    }

    template<typename T> void GlobalSettings<T>::DestroySettings() {
        RemoveUsePoint();
    }
}

#endif //SRENGINE_SETTINGS_H
