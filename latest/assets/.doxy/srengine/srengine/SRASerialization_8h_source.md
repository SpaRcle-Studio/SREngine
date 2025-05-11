

# File SRASerialization.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**SRASerialization.h**](SRASerialization_8h.md)

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


