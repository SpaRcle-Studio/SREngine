

# File PassKey.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**PassKey.h**](PassKey_8h.md)

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
    class Passkey : private Passkey<Others, false> ... {
    public:
        template <typename U, typename = typename std::enable_if<AllowSuccessor && std::is_base_of<T, U>::value && !std::is_same<U, T>::value, T>::type>
        Passkey(Passkey<U>&&) { }

        template <typename U, typename = U, typename = typename std::enable_if<std::is_base_of<Passkey<U>, Passkey<T, AllowSuccessor, Others...>>::value, U>::type>
        Passkey(Passkey<U>&&) { }

        template <typename U, typename = U, typename = U, typename = typename std::enable_if<(AllowSuccessor || (sizeof...(Others) > 0)) && std::is_same<U, T>::value, T>::type>
        Passkey(Passkey<U, AllowSuccessor, Others...>&&) { }

    protected:
        Passkey() noexcept = default;
        explicit Passkey(const T *) noexcept { }

    private:
        friend T;

        Passkey(Passkey<T, false>&&) { }

        Passkey(const Passkey&) = delete;
        Passkey& operator=(const Passkey&) = delete;
        Passkey& operator=(Passkey&&) = delete;

    };

    template<typename T> Passkey(const T*) -> Passkey<T>;
}

#endif //SR_COMMON_PASS_KEY_H
```


