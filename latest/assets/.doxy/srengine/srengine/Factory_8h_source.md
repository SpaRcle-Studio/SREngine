

# File Factory.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**Factory.h**](Factory_8h.md)

[Go to the documentation of this file](Factory_8h.md)


```C++
//
// Created by Monika on 17.10.2024.
//

#ifndef SR_COMMON_TYPE_TRAITS_FACTORY_H
#define SR_COMMON_TYPE_TRAITS_FACTORY_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/TypeTraits/SRClassMeta.h>

namespace SR_UTILS_NS {
    class SRClassMeta;

    class SR_COMMON_DLL_API BaseFactory {
    public:
        virtual ~BaseFactory() = default;

        SR_NODISCARD virtual const SRClassMeta* GetType(SR_UTILS_NS::StringAtom name) const = 0;

        SR_NODISCARD bool IsRegistered(const SRClassMeta* pMeta) const {
            return pMeta && GetType(pMeta->GetFactoryName()) == pMeta;
        }
    };

    class SR_COMMON_DLL_API Factory : public BaseFactory {
        using AllocatorT = std::function<SRClass*()>;
        using MetaGetterT = const SRClassMeta*(*)();
        struct TypeInfo {
            SR_UTILS_NS::StringAtom moduleName;
            AllocatorT allocator;
            MetaGetterT metaGetter = nullptr;
            bool isAbstract = false;
            uint64_t version = 0;
        };
    public:
        SR_NODISCARD static Factory& Instance() noexcept;

        SR_NODISCARD SR_UTILS_NS::StringAtom GetName(const SRClassMeta* pMeta, bool isMustExists = true) const;

        template<class T> bool Register(SR_UTILS_NS::StringAtom moduleName);
        template<class T> bool Unregister();

        template<class Y> SR_NODISCARD SR_UTILS_NS::StringAtom GetName(Y* pObject, const bool isMustExists = true) const {
            if (SRVerify(pObject)) {
                return GetName(pObject->GetMeta(), isMustExists);
            }
            return {};
        }

        template<class Y> SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const {
            return GetName(Y::GetMetaStatic(), true);
        }

        template<typename T> SR_NODISCARD SR_HTYPES_NS::SharedPtr<T> Create(SR_UTILS_NS::StringAtom name) const noexcept {
            SR_TRACY_ZONE;

            if constexpr (SR_UTILS_NS::IsSharedPointerV<T>) {
                if (auto&& pClass = CreateBase(name)) {
                    if (auto&& pCasted = dynamic_cast<T*>(pClass)) {
                        return SR_HTYPES_NS::SharedPtr<T>(pCasted);
                    }
                    SRHalt("Failed to cast object \"{}\" to type \"{}\"!", name, typeid(T).name());
                    return nullptr;
                }
                return nullptr;
            }
            else {
                static_assert(AlwaysFalseV<T>, "Type must be shared pointer! Or your class has private inheritance from SharedPtr!");
                return nullptr;
            }
        }

        template<typename T> SR_NODISCARD SR_HTYPES_NS::SharedPtr<T> Create() const noexcept {
            return Create<T>(T::GetClassStaticName());
        }

        SR_NODISCARD SRClass* CreateBase(SR_UTILS_NS::StringAtom name) const noexcept;
        SR_NODISCARD std::vector<SR_UTILS_NS::StringAtom> GetInheritances(SR_UTILS_NS::StringAtom baseClass) const noexcept;
        SR_NODISCARD bool IsAbstract(SR_UTILS_NS::StringAtom name) const noexcept;
        SR_NODISCARD const SRClassMeta* GetType(SR_UTILS_NS::StringAtom name) const noexcept override;
        SR_NODISCARD const TypeInfo* GetTypeInfo(SR_UTILS_NS::StringAtom name) const noexcept;
        SR_NODISCARD void ForEachClassInModule(SR_UTILS_NS::StringAtom moduleName, const std::function<void(const SRClassMeta*)>& func) const noexcept;

    private:
        void WriteLog(const std::string& message) const noexcept;
        void WriteError(const std::string& message) const noexcept;

    private:
        std::unordered_map<SR_UTILS_NS::StringAtom, TypeInfo> m_types;

    };

    template<class T> bool Factory::Register(SR_UTILS_NS::StringAtom moduleName) {
        if constexpr (std::is_same_v<T, void>) {
            static_assert(AlwaysFalseV<T>, "Type must be specified!");
        }
        else if constexpr (!std::is_default_constructible_v<T> && !std::is_abstract_v<T>) {
            static_assert(AlwaysFalseV<T>, "Non abstract type must be default constructible!");
        }
        else if (auto&& pMeta = T::GetMetaStatic()) {
            auto&& name = pMeta->GetFactoryName();

            if (m_types.count(name) > 0) {
                WriteError("Factory::Register() : type \"{}\" is already registered!"_format(name));
                return false;
            }

            WriteLog("Factory::Register() : registering type \"{}\""_format(name));

            TypeInfo& info = m_types[name];

            if constexpr (std::is_abstract_v<T>) {
                info.isAbstract = true;
            }
            else {
                info.allocator = []() -> SRClass * {
                    return static_cast<SRClass *>(SRNew<T>());
                };
            }

            info.moduleName = moduleName;
            info.metaGetter = T::GetMetaStatic;
            info.version = pMeta->GetVersion();
            return true;
        }

        return false;
    }

    template<class T> bool Factory::Unregister() {
        if (auto&& pMeta = T::GetMetaStatic()) {
            auto&& name = pMeta->GetFactoryName();

            auto&& pIt = m_types.find(name);
            if (pIt == m_types.end()) {
                WriteError("Factory::Register() : type \"{}\" is not registered!"_format(name));
                return false;
            }

            WriteLog("Factory::Unregister() : unregistering type \"{}\""_format(name));

            m_types.erase(pIt);
            return true;
        }

        return false;
    }
}

#endif //SR_COMMON_TYPE_TRAITS_FACTORY_H
```


