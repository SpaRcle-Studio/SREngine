

# File PassKey.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**PassKey.h**](PassKey_8h.md)

[Go to the documentation of this file](PassKey_8h.md)


```C++
//
// Created by Monika on 22.08.2024.
//

#ifndef SR_COMMON_PASS_KEY_H
#define SR_COMMON_PASS_KEY_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    template <typename T, bool AllowSuccessor = false, typename ... Others>
    class PassKey : private PassKey<Others, false> ... {
    public:
        template <typename U, typename = typename std::enable_if<AllowSuccessor && std::is_base_of<T, U>::value && !std::is_same<U, T>::value, T>::type>
        PassKey(PassKey<U>&&) { }

        template <typename U, typename = U, typename = typename std::enable_if<std::is_base_of<PassKey<U>, PassKey<T, AllowSuccessor, Others...>>::value, U>::type>
        PassKey(PassKey<U>&&) { }

        template <typename U, typename = U, typename = U, typename = typename std::enable_if<(AllowSuccessor || (sizeof...(Others) > 0)) && std::is_same<U, T>::value, T>::type>
        PassKey(PassKey<U, AllowSuccessor, Others...>&&) { }

    protected:
        PassKey() noexcept = default;
        explicit PassKey(const T *) noexcept { }

    private:
        friend T;

        PassKey(PassKey<T, false>&&) { }

        PassKey(const PassKey&) = delete;
        PassKey& operator=(const PassKey&) = delete;
        PassKey& operator=(PassKey&&) = delete;

    };

    template<typename T> PassKey(const T*) -> PassKey<T>;
}

#endif //SR_COMMON_PASS_KEY_H
```


