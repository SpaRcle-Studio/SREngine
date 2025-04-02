

# File SRClass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TypeTraits**](dir_16c2d3fce5275752976e0da6f3af1bdb.md) **>** [**SRClass.h**](SRClass_8h.md)

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

        virtual void InitializeClass() noexcept { }

        static SR_UTILS_NS::StringAtom GetClassStaticName() noexcept;
        static const SR_UTILS_NS::SRClassMeta* GetMetaStatic() noexcept;
        static SR_UTILS_NS::SRClass* AllocateStatic() noexcept;
        static bool RegisterPropertiesCodegen();

    private:
        void SR_CLANG_CODEGEN_MARKER() { }

    };

    template<class T> static T* PostAllocationInitialize(T* pObject) {
        pObject->InitializeClass();
        return pObject;
    }
}

template<class T, typename ...Args> static T* SRNew(Args&& ...args) {
     return PostAllocationInitialize(new T(std::forward<Args>(args)...));
}

#endif //SR_ENGINE_UTILS_TYPE_TRAITS_SR_CLASS_H
```


