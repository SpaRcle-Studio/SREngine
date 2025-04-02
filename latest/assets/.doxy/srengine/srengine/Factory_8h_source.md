

# File Factory.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TypeTraits**](dir_16c2d3fce5275752976e0da6f3af1bdb.md) **>** [**Factory.h**](Factory_8h.md)

[Go to the documentation of this file](Factory_8h.md)


```C++
//
// Created by Monika on 17.10.2024.
//

#ifndef SR_COMMON_TYPE_TRAITS_FACTORY_H
#define SR_COMMON_TYPE_TRAITS_FACTORY_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/TypeTraits/SRClassMeta.h>

namespace SR_UTILS_NS {
    class SRClassMeta;

    class BaseFactory {
    public:
        virtual ~BaseFactory() = default;

        SR_NODISCARD virtual const SRClassMeta* GetType(SR_UTILS_NS::StringAtom name) const = 0;

        SR_NODISCARD bool IsRegistered(const SRClassMeta* pMeta) const {
            return pMeta && GetType(pMeta->GetFactoryName()) == pMeta;
        }
    };

    class Factory : public BaseFactory {
        using AllocatorT = std::function<SRClass*()>;
        using MetaGetterT = const SRClassMeta*(*)();
        struct TypeInfo {
            AllocatorT allocator;
            MetaGetterT metaGetter = nullptr;
            bool isAbstract = false;
            uint64_t version = 0;
        };
    public:
        SR_NODISCARD static Factory& Instance() noexcept;

        SR_NODISCARD SR_UTILS_NS::StringAtom GetName(const SRClassMeta* pMeta, bool isMustExists = true) const;

        template<class T> bool Register() {
            if constexpr (std::is_abstract_v<T>) {
                if (auto&& pMeta = T::GetMetaStatic()) {
                    auto&& name = pMeta->GetFactoryName();
                    TypeInfo& info = m_types[name];
                    info.isAbstract = true;
                    info.metaGetter = T::GetMetaStatic;
                    info.version = pMeta->GetVersion();
                }
                else {
                    SR_PLATFORM_NS::WriteConsoleError("Failed to get meta for abstract class!");
                }
                return false;
            }
            else if constexpr (std::is_same_v<T, void>) {
                static_assert(AlwaysFalseV<T>, "Type must be specified!");
            }
            else if constexpr (!std::is_default_constructible_v<T>) {
                static_assert(AlwaysFalseV<T>, "Type must be default constructible!");
            }
            else if (auto&& pMeta = T::GetMetaStatic()) {
                auto&& name = pMeta->GetFactoryName();
                TypeInfo& info = m_types[name];
                info.allocator = []() -> SRClass* {
                    return static_cast<SRClass*>(SRNew<T>());
                };
                info.metaGetter = T::GetMetaStatic;
                info.version = pMeta->GetVersion();
                return true;
            }
            return false;
        }

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

        SR_NODISCARD SRClass* CreateBase(SR_UTILS_NS::StringAtom name) const noexcept {
            auto&& pIt = m_types.find(name);

            if (pIt != m_types.end()) {
                if (pIt->second.isAbstract) {
                    SR_ERROR("Factory::CreateBase() : type \"{}\" is abstract!", name);
                    return nullptr;
                }

                auto&& pClass = pIt->second.allocator();
                if (pClass) {
                    return pClass;
                }

                SRHalt("Failed to create object \"{}\"!", name);
                return nullptr;
            }

            SRHalt("Type \"{}\" is not registered!", name);
            return nullptr;
        }

        SR_NODISCARD std::vector<SR_UTILS_NS::StringAtom> GetInheritances(SR_UTILS_NS::StringAtom baseClass) const noexcept;

        SR_NODISCARD bool IsAbstract(SR_UTILS_NS::StringAtom name) const noexcept;

        SR_NODISCARD const SRClassMeta* GetType(SR_UTILS_NS::StringAtom name) const noexcept override {
            auto&& pIt = m_types.find(name);
            if (pIt != m_types.end()) {
                return pIt->second.metaGetter();
            }
            return nullptr;
        }

    private:
        std::unordered_map<SR_UTILS_NS::StringAtom, TypeInfo> m_types;

    };
}

#endif //SR_COMMON_TYPE_TRAITS_FACTORY_H
```


