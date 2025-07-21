

# File ToString.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**ToString.h**](ToString_8h.md)

[Go to the documentation of this file](ToString_8h.md)


```C++
//
// Created by Monika on 19.11.2023.
//

#ifndef SR_ENGINE_UTILS_TO_STRING_H
#define SR_ENGINE_UTILS_TO_STRING_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Math/Mathematics.h>

namespace SR_UTILS_NS {
    static SR_INLINE std::string SerializeDouble(double_t value) {
        char buffer[64];
        std::snprintf(buffer, sizeof(buffer), "%.17g", value);
        return std::string(buffer);
    }

    static SR_INLINE std::string SerializeFloat(float value) {
        char buffer[64];
        std::snprintf(buffer, sizeof(buffer), "%.9g", value);
        return std::string(buffer);
    }

    template<typename T> std::string ToString(const T& value) {
        if constexpr (IsLogical<T>()) {
            return value ? "true" : "false";
        }
        else if constexpr (SR_MATH_NS::IsNumber<T>()) {
            return std::to_string(value);
        }
        else if constexpr (IsString<T>()) {
            return value;
        }
        else if constexpr (std::is_enum_v<T>) {
            return SR_UTILS_NS::EnumReflector::ToStringAtom(value);
        }
        else {
            std::cerr << "ToStringAtom: unsupported type!" << std::endl;
            SR_MAKE_BREAKPOINT;
            return std::string(); 
        }
    }
}

#endif //SR_ENGINE_UTILS_TO_STRING_H
```


