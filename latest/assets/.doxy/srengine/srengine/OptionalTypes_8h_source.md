

# File OptionalTypes.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**OptionalTypes.h**](OptionalTypes_8h.md)

[Go to the documentation of this file](OptionalTypes_8h.md)


```C++
//
// Created by Monika on 26.07.2025.
//

#ifndef SR_COMMON_SERIALIZATION_OPTIONAL_TYPES_H
#define SR_COMMON_SERIALIZATION_OPTIONAL_TYPES_H

#include <Utils/Serialization/Serializable.h>

namespace SR_UTILS_NS {
    /*class SR_COMMON_DLL_API OptionalFloat : public Serializable {
        using Super = Serializable;
        SR_CLASS()
    public:
        OptionalFloat();
        OptionalFloat(float_t value);

        ~OptionalFloat() override;

        OptionalFloat(const OptionalFloat& other);
        OptionalFloat(OptionalFloat&& other) noexcept;

        OptionalFloat& operator=(const OptionalFloat& other);
        OptionalFloat& operator=(OptionalFloat&& other) noexcept;

        SR_NODISCARD bool IsSet() const noexcept;

        operator float_t() const noexcept;
        operator float_t&() noexcept;

        OptionalFloat& operator=(float_t value) noexcept;

    private:
        float m_value = 0.0f;
        bool m_isSet = false;

    };*/
}

#endif //SR_COMMON_SERIALIZATION_OPTIONAL_TYPES_H
```


