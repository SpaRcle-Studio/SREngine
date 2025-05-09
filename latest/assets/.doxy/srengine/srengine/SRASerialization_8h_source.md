

# File SRASerialization.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**SRASerialization.h**](SRASerialization_8h.md)

[Go to the documentation of this file](SRASerialization_8h.md)


```C++
//
// Created by Monika on 17.10.2024.
//

#ifndef SR_COMMON_SERIALIZATION_SRA_SERIALIZATION_H
#define SR_COMMON_SERIALIZATION_SRA_SERIALIZATION_H

#include <Utils/Serialization/BaseSerialization.h>

namespace SR_UTILS_NS {

    class SRAISerialization : public IBaseSerialization {
    public:
        void SetUseTabs(const bool value) noexcept { m_isNeedUseTabs = value; }
        SR_NODISCARD bool IsNeedUseTabs() const noexcept { return m_isNeedUseTabs; }

        SR_NODISCARD std::string ToStringBase() const noexcept override;

    private:
        bool m_isNeedUseTabs = false;

    };

    class SRADeserializer;

    class SRASerializer : public IBaseSerializer, public SRAISerialization {
    public:
        SRASerializer();

    public:
        SR_NODISCARD std::unique_ptr<IDeserializer> CreateDeserializer() const override;

    private:
        SR_NODISCARD bool IsAllowEmptyElementsInArrayImpl() const noexcept override { return IsAllowEmptyElementsInArray(); }

    };

    class SRADeserializer : public IBaseDeserializer, public SRAISerialization {
        friend SRASerializer;
    public:
        SR_NODISCARD bool LoadFromFile(const SR_UTILS_NS::Path& path) override;
        SR_NODISCARD bool LoadFromString(const std::string& str) override;
        SR_NODISCARD bool LoadFromNode(SR_UTILS_NS::SerializationNode&& node);

        SR_NODISCARD bool ShouldSetDefaults(const SerializationId& name) const noexcept override { return true; }
        SR_NODISCARD bool ShouldSetDefaults() const noexcept override { return true; }
        SR_NODISCARD bool AllowNewMapKeys() const noexcept override { return false; }
        SR_NODISCARD bool IsPreserveMode() const noexcept override { return false; }
        SR_NODISCARD bool AllowReAllocPointer(ReAllocPointerReason reason) const noexcept override { return false; }

        void ReportError(const std::string& message) override;

    };
}

#endif //SR_COMMON_SERIALIZATION_SRA_SERIALIZATION_H
```


