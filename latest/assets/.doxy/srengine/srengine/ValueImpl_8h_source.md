

# File ValueImpl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Reflection**](dir_a5a26934b95143030003946f011a899c.md) **>** [**ValueImpl.h**](ValueImpl_8h.md)

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


