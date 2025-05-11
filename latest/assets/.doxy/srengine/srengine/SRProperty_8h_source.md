

# File SRProperty.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**SRProperty.h**](SRProperty_8h.md)

[Go to the documentation of this file](SRProperty_8h.md)


```C++
//
// Created by Monika on 14.10.2024.
//

#ifndef SR_ENGINE_UTILS_TYPE_TRAITS_SR_PROPERTY_H
#define SR_ENGINE_UTILS_TYPE_TRAITS_SR_PROPERTY_H

#include <Utils/Serialization/Serializable.h>
#include <Utils/Types/StringAtom.h>

namespace SR_UTILS_NS {
    class SRPropertyVariant {
        ~SRPropertyVariant() = default;

        SR_ENUM_CLASS_T(Type, uint8_t,
            Float, Double, String, StringAtom, Bool,
            Int8, Int16, Int32, Int64,
            UInt8, UInt16, UInt32, UInt64,
            Unknown
        );

        struct Object {
            StringAtom type;
            SR_UTILS_NS::Serializable value;
        };

        /*union SRPropertyData {
            float m_float;
            double m_double;
            std::string m_string;
            StringAtom m_stringAtom;
            bool m_bool;
            int8_t m_int8;
            int16_t m_int16;
            int32_t m_int32;
            int64_t m_int64;
            uint8_t m_uint8;
            uint16_t m_uint16;
            uint32_t m_uint32;
            uint64_t m_uint64;
        };*/
    };

    class SRProperty {
    private:
        StringAtom m_name;
        StringAtom m_type;
        StringAtom m_description;

    };
}

#endif //SR_ENGINE_UTILS_TYPE_TRAITS_SR_PROPERTY_H
```


