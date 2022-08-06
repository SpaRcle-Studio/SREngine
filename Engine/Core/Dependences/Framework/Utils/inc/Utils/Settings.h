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

    public:
        bool Destroy() final;

    protected:
        virtual void ClearSettings() { }
        virtual bool LoadSettings(const Xml::Node& node) { return true; }

        bool Reload() final;

    protected:
        SR_NODISCARD Path GetResourcePath() const override;
        SR_NODISCARD Path GetAssociatedPath() const override;
        SR_NODISCARD SR_XML_NS::Document LoadDocument() const;

    private:
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

            if (!Singleton<T>::Instance().IsValid()) {
                return;
            }

            Singleton<T>::Instance().RemoveUsePoint();
            Singleton<T>::Instance().ForceDestroy();

            /// Форсированно уничтожаем этот ресурс, чтобы не ждать пока закончится время жизни
            ResourceManager::Instance().Synchronize(true);
        }

    protected:
        ~GlobalSettings() override = default;

    private:
        void OnSingletonDestroy() final;
        void InitSingleton() final;
        bool IsSingletonCanBeDestroyed() const final { return false; }
        void RemoveUsePoint() final;

    };

    template<typename T> void GlobalSettings<T>::OnSingletonDestroy() {
        Singleton<T>::OnSingletonDestroy();
    }

    template<typename T> void GlobalSettings<T>::InitSingleton() {
        auto&& path = GetResourcePath();

        SetId(path);

        AddUsePoint();

        if (!Reload()) {
            SR_ERROR("GlobalSettings<T>::InitSingleton() : failed to reload settings!");
        }

        Singleton<T>::InitSingleton();
    }

    template<typename T> void GlobalSettings<T>::RemoveUsePoint() {
        SRAssert2(m_countUses > 0, "count use points is zero!");
        --m_countUses;
    }
}

#endif //SRENGINE_SETTINGS_H
