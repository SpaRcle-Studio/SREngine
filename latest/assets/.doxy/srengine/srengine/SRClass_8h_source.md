

# File SRClass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**SRClass.h**](SRClass_8h.md)

[Go to the documentation of this file](SRClass_8h.md)


```C++
//
// Created by Monika on 02.04.2024.
//

#ifndef SR_ENGINE_UTILS_TYPE_TRAITS_SR_CLASS_H
#define SR_ENGINE_UTILS_TYPE_TRAITS_SR_CLASS_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Types/Marshal.h>
#include <Utils/TypeTraits/ClassDB.h>
#include <Utils/TypeTraits/SRClassMeta.h>

namespace SR_UTILS_NS {
    class SRClassMeta;

    SR_ENUM_NS_STRUCT_T(SerializationFlags, uint64_t,
        None     = 1 << 0,
        Compress = 1 << 1,
        NoUID    = 1 << 2,
        DontSave = 1 << 3
    )

    struct SerializableVerifyContext {
    public:
        void AddError(const std::string& error) noexcept { errors.insert(error); }
        void AddWarning(const std::string& warning) noexcept { warnings.insert(warning); }

        SR_NODISCARD const std::set<std::string>& GetErrors() const noexcept { return errors; }
        SR_NODISCARD const std::set<std::string>& GetWarnings() const noexcept { return warnings; }

    private:
        std::set<std::string> errors;
        std::set<std::string> warnings;
    };

    class SRClass {
    public:
        virtual ~SRClass() = default;

    public:
        SR_NODISCARD static std::span<const SRClassMeta*> GetBaseMetas() noexcept {
            return {};
        }

        SR_NODISCARD virtual const SR_UTILS_NS::SRClassMeta* GetMeta() const noexcept = 0;

        //virtual void InitializeClass() noexcept { }

        static SR_UTILS_NS::StringAtom GetClassStaticName() noexcept;
        static const SR_UTILS_NS::SRClassMeta* GetMetaStatic() noexcept;
        static SR_UTILS_NS::SRClass* AllocateStatic() noexcept;
        static bool RegisterPropertiesCodegen();

    private:
        void SR_CLANG_CODEGEN_MARKER() { }

    };

    template<typename T>
    constexpr bool IsSRClassV = std::is_base_of_v<SRClass, RemoveQualifiersT<T>> || std::is_same_v<SRClass, RemoveQualifiersT<T>>;

    //template<class T> static T* PostAllocationInitialize(T* pObject) {
    //    if constexpr (std::is_base_of_v<SRClass, T>) {
    //        pObject->InitializeClass();
    //    }
    //    return pObject;
    //}
}

//template<class T, typename ...Args> static T* SRNew(Args&& ...args) {
//     return PostAllocationInitialize(new T(std::forward<Args>(args)...));
//}

#endif //SR_ENGINE_UTILS_TYPE_TRAITS_SR_CLASS_H
```


