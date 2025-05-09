

# File SRClassMeta.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TypeTraits**](dir_16c2d3fce5275752976e0da6f3af1bdb.md) **>** [**SRClassMeta.h**](SRClassMeta_8h.md)

[Go to the documentation of this file](SRClassMeta_8h.md)


```C++
//
// Created by Monika on 16.10.2024.
//

#ifndef SR_COMMON_TYPE_TRAITS_SR_CLASS_META_H
#define SR_COMMON_TYPE_TRAITS_SR_CLASS_META_H

#include <Utils/Types/StringAtom.h>
#include <Utils/Serialization/Serializer.h>
#include <Utils/Serialization/Deserializer.h>

namespace SR_UTILS_NS {
    namespace Reflection {
        class Property;
    }

    class Serializable;

    class SR_COMMON_DLL_API SRClassMeta {
    public:
        virtual ~SRClassMeta();

        virtual void Save(SR_UTILS_NS::ISerializer& serializer, const SR_UTILS_NS::Serializable& obj) const;
        virtual bool Load(SR_UTILS_NS::IDeserializer& deserializer, SR_UTILS_NS::Serializable& obj) const;

        SR_NODISCARD bool IsInherited(SR_UTILS_NS::StringAtom baseClass) const noexcept;

        void ForEachProperty(const std::function<void(const SR_UTILS_NS::Reflection::Property& property, uint64_t index)>& func, uint64_t* pIndex = nullptr) const;

        SR_NODISCARD virtual SR_UTILS_NS::StringAtom GetInspectorName() const noexcept;

        SR_NODISCARD uint64_t GetVersion() const noexcept;

        SR_NODISCARD virtual std::span<const SR_UTILS_NS::StringAtom> GetCategory() const noexcept;
        SR_NODISCARD virtual bool IsAbstract() const noexcept;
        SR_NODISCARD virtual bool IsHidden() const noexcept;
        SR_NODISCARD virtual bool IsEditorOnly() const noexcept;
        SR_NODISCARD virtual std::span<const SRClassMeta*> GetBaseMetas() const noexcept;
        SR_NODISCARD virtual std::span<const SR_UTILS_NS::Reflection::Property> GetProperties() const noexcept;
        SR_NODISCARD virtual SR_UTILS_NS::StringAtom GetFactoryName() const noexcept;
        SR_NODISCARD virtual SRClass* Allocate() const noexcept;

    protected:
        SR_NODISCARD virtual uint64_t GetVersionImpl() const noexcept;

    private:
        mutable uint64_t m_versionCached = SR_UINT64_MAX;

    };
};

namespace Codegen {
    template<class T> struct SRClassMetaTemplate : public SR_UTILS_NS::SRClassMeta { };
}

#define SR_CLASS_BASE()                                                                                                 \
    public:                                                                                                             \
        static bool RegisterPropertiesCodegen();                                                                        \
    private:                                                                                                            \
        template<typename TSerializeType> friend struct ::Codegen::SRClassMetaTemplate;                                 \
        friend class SR_UTILS_NS::SRClass;                                                                              \
                                                                                                                        \
    public:                                                                                                             \
        static const SR_UTILS_NS::SRClassMeta* GetMetaStatic() noexcept;                                                \
        const SR_UTILS_NS::SRClassMeta* GetMeta() const noexcept override {                                             \
            auto&& pStaticMetaFromClass = GetMetaStatic();                                                              \
            SRAssert2(pStaticMetaFromClass, std::string("No static meta for: ") + typeid(*this).name());                \
            return pStaticMetaFromClass;                                                                                \
        }                                                                                                               \
                                                                                                                        \
        static SR_UTILS_NS::StringAtom GetClassStaticName() noexcept;                                                   \
        static SRClass* AllocateStatic() noexcept;                                                                      \


#define SR_CLASS()                                                                                                      \
        SR_CLASS_BASE()                                                                                                 \
    private:                                                                                                            \


#define SR_STRUCT()                                                                                                     \
        SR_CLASS_BASE()                                                                                                 \
    public:                                                                                                             \


#define SR_CLASS_REGISTER_PROPERTY_BASE(className, propertyName, propertyType)                                          \

#define SR_VIRTUAL_PROPERTY                                                                                             \
    typedef bool SR_COMBINE(SR_CODEGEN_VIRTUAL_PROP_LINE_, __LINE__);                                                   \

//#define SR_VIRTUAL_PROPERTY void SR_COMBINE(SR_CODEGEN_VIRTUAL_PROP_ANCHOR_LINE_, __LINE__)() {}

#endif //SR_COMMON_TYPE_TRAITS_SR_CLASS_META_H
```


