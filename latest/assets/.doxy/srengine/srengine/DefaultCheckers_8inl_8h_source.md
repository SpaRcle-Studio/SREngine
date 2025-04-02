

# File DefaultCheckers.inl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**DefaultCheckers.inl.h**](DefaultCheckers_8inl_8h.md)

[Go to the documentation of this file](DefaultCheckers_8inl_8h.md)


```C++
//
// Created by Monika on 17.10.2024.
//

template<class T> struct DefaultChecker<T, typename std::enable_if_t<std::is_default_constructible_v<T> && CheckOperatorUsableV<CheckerEqualityComparable, T, T> && !SerializationTraits<T>::HasEmpty && !std::is_same_v<T, SR_UTILS_NS::StringAtom>>> {
    static bool IsDefault(const T& value) {
        return SR_EQUALS(value, T {});
    }
};

template<> struct DefaultChecker<SR_UTILS_NS::StringAtom> {
    static bool IsDefault(const SR_UTILS_NS::StringAtom& value) {
        return value.Empty();
    }
};

template<class T> struct DefaultChecker<std::optional<T>> {
    static bool IsDefault(const std::optional<T>& value) {
        return !value.is_initialized();
    }
};

template<class T>
struct DefaultChecker<T, std::enable_if_t<SerializationTraits<T>::HasEmpty && !IsTypeFromStdArrayTemplateV<T>>> {
    static bool IsDefault(const T& value) {
        return value.empty();
    }
};

template<class T, size_t N>
struct DefaultChecker<std::array<T, N>> {
    using IsAlwaysFalse = std::bool_constant<(N > 0)>;

    static constexpr bool IsDefault(const std::array<T, N>& value) {
        return value.empty();
    }
};
```


