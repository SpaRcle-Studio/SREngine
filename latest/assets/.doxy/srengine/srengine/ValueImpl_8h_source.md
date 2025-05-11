

# File ValueImpl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Reflection**](dir_b9e652b456a4d9b315741a759a2b0c5c.md) **>** [**ValueImpl.h**](ValueImpl_8h.md)

[Go to the documentation of this file](ValueImpl_8h.md)


```C++
//
// Created by Monika on 31.01.2025.
//

#ifndef SR_UTILS_TYPE_TRAITS_VALUE_IMPL_H
#define SR_UTILS_TYPE_TRAITS_VALUE_IMPL_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Common/TypeInfo.h>
#include <Utils/Types/StringAtom.h>

namespace SR_UTILS_NS::Reflection {
    /*SR_ENUM_NS_CLASS_T(ValueTypeKind, uint8_t,
        None,
        Numeric, Boolean,
        String, StringAtom, UnicodeString,
        Array, Map, Set,
        Enum,
        Object,
        Ptr
    );*/

    /*class ValueImpl : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::NonMovable, public SR_UTILS_NS::ICloneable {
    public:
        SR_NODISCARD virtual StandardType GetType() const noexcept = 0;

        SR_NODISCARD bool IsReference() const noexcept { return m_pReference != nullptr; }

    protected:
        SR_NODISCARD void* GetReference() const noexcept { return m_pReference; }

    private:
        void* m_pReference = nullptr;

    };

    class ValueImplArray : public ValueImpl {
    private:
        std::vector<ValueImpl*> m_values;
        StandardType m_containerType = StandardType::Unknown;

    };

    class ValueImplMap : public ValueImpl {
    private:
        std::map<SRHashType, ValueImpl*> m_values;
        StandardType m_containerType = StandardType::Unknown;

    };

    class ValueImplVector : public ValueImpl {
    private:
        StandardType m_vectorType = StandardType::Unknown;
        uint8_t m_dimension = 0;

    };*/
}

#endif //SR_UTILS_TYPE_TRAITS_VALUE_IMPL_H
```


